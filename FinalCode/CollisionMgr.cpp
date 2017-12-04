#include "Stdafx.h"
#include "CollisionMgr.h"

#include "DeviceMgr.h"
#include "CameraMgr.h"
#include "PathFindMgr.h"
#include "Object.h"
#include "TransformCom.h"
#include "CollisionCom.h"
#include "PathFindCom.h"

IMPLEMENT_SINGLETON(CCollisionMgr)

CCollisionMgr::CCollisionMgr()
{
}

CCollisionMgr::~CCollisionMgr()
{
	Release();
}

void CCollisionMgr::Initialize()
{
}

int CCollisionMgr::Update()
{
	// PlayerToMonster
	for(size_t i = 0; i < m_ObjectVec[COLL_TYPE_PLAYER].size(); ++i)
	{
		for(size_t j = 0; j < m_ObjectVec[COLL_TYPE_MONSTER].size() && i < m_ObjectVec[COLL_TYPE_PLAYER].size(); ++j)
			PlayerToMonster(m_ObjectVec[COLL_TYPE_PLAYER][i], m_ObjectVec[COLL_TYPE_MONSTER][j]);
	}

	// MonsterToMonster
	for(size_t i = 0; i < m_ObjectVec[COLL_TYPE_MONSTER].size(); ++i)
	{
		for(size_t j = i + 1; j < m_ObjectVec[COLL_TYPE_MONSTER].size(); ++j)
			MonsterToMonster(m_ObjectVec[COLL_TYPE_MONSTER][i], m_ObjectVec[COLL_TYPE_MONSTER][j]);
	}

	// PlayerToEffect
	for(size_t i = 0; i < m_ObjectVec[COLL_TYPE_PLAYER].size(); ++i)
	{
		for(size_t j = 0; j < m_ObjectVec[COLL_TYPE_MONSTER_EFFECT].size() && i < m_ObjectVec[COLL_TYPE_PLAYER].size(); ++j)
			PlayerToEffect(m_ObjectVec[COLL_TYPE_PLAYER][i], m_ObjectVec[COLL_TYPE_MONSTER_EFFECT][j]);
	}

	// MonsterToEffect
	for(size_t i = 0; i < m_ObjectVec[COLL_TYPE_MONSTER].size(); ++i)
	{
		for(size_t j = 0; j < m_ObjectVec[COLL_TYPE_PLAYER_EFFECT].size() && i < m_ObjectVec[COLL_TYPE_MONSTER].size(); ++j)
			MonsterToEffect(m_ObjectVec[COLL_TYPE_MONSTER][i], m_ObjectVec[COLL_TYPE_PLAYER_EFFECT][j]);
	}

	// PlayerToNPC
	for(size_t i = 0; i < m_ObjectVec[COLL_TYPE_PLAYER].size(); ++i)
	{
		for(size_t j = 0; j < m_ObjectVec[COLL_TYPE_NPC].size(); ++j)
			PlayerToNPC(m_ObjectVec[COLL_TYPE_PLAYER][i], m_ObjectVec[COLL_TYPE_NPC][j]);
	}

	// PlayerToProb
	for(size_t i = 0; i < m_ObjectVec[COLL_TYPE_PLAYER].size(); ++i)
	{
		for(size_t j = 0; j < m_ObjectVec[COLL_TYPE_PROB].size(); ++j)
			PlayerToProb(m_ObjectVec[COLL_TYPE_PLAYER][i], m_ObjectVec[COLL_TYPE_PROB][j]);
	}

	for(int i = 0; i < COLL_TYPE_END; ++i)
		m_ObjectVec[i].clear();

	return 0;
}

void CCollisionMgr::Render()
{
	if(CSettingMgr::GetInstance()->GetGameMode() & GAME_MODE_CHECK_SPHERE)
	{
		for(int i = 0; i < COLL_TYPE_END; ++i)
		{
			for(size_t j = 0; j < m_ObjectVec[i].size(); ++j)
			{
				// CollisionCom
				CCollisionCom* pCollisionCom = (CCollisionCom*)m_ObjectVec[i][j]->GetComponent(COM_TYPE_COLLISION);

				// Sphere
				Sphere* pSphere = pCollisionCom->m_pCheckSphere;
				if(pSphere == NULL)
					continue;

				// Center
				D3DXVECTOR3 vCenter;
				D3DXVec3TransformCoord(&vCenter, &pSphere->vCenter, pSphere->pMatrix);

				// World
				D3DXMATRIX mWorld;
				D3DXMatrixTranslation(&mWorld, vCenter.x, vCenter.y, vCenter.z);
				D3DXMatrixMultiply(&mWorld, &mWorld, CCameraMgr::GetInstance()->GetViewProj());

				// SetTransform
				CDeviceMgr::GetInstance()->GetDevice()->SetTransform(D3DTS_WORLD, &mWorld);

				// CreateSphere
				LPD3DXMESH pMesh;
				D3DXCreateSphere(CDeviceMgr::GetInstance()->GetDevice(), pSphere->fRadius, 4, 4, &pMesh, NULL);

				// Draw
				pMesh->DrawSubset(0);

				// Release
				pMesh->Release();
			}
		}
	}

	if(CSettingMgr::GetInstance()->GetGameMode() & GAME_MODE_COLLISION_SPHERE)
	{
		for(int i = 0; i < COLL_TYPE_END; ++i)
		{
			for(size_t j = 0; j < m_ObjectVec[i].size(); ++j)
			{
				// CollisionCom
				CCollisionCom* pCollisionCom = (CCollisionCom*)m_ObjectVec[i][j]->GetComponent(COM_TYPE_COLLISION);

				// Sphere
				Sphere* pSphere = pCollisionCom->m_pCollisionSphere;

				// Box
				Collision* pBox = pCollisionCom->m_pCollisionBox;

				if(pSphere != NULL)
				{
					// Center
					D3DXVECTOR3 vCenter;
					D3DXVec3TransformCoord(&vCenter, &pSphere->vCenter, pSphere->pMatrix);

					// World
					D3DXMATRIX mWorld;
					D3DXMatrixTranslation(&mWorld, vCenter.x, vCenter.y, vCenter.z);
					D3DXMatrixMultiply(&mWorld, &mWorld, CCameraMgr::GetInstance()->GetViewProj());

					// SetTransform
					CDeviceMgr::GetInstance()->GetDevice()->SetTransform(D3DTS_WORLD, &mWorld);

					// CreateSphere
					LPD3DXMESH pMesh;
					D3DXCreateSphere(CDeviceMgr::GetInstance()->GetDevice(), pSphere->fRadius, 4, 4, &pMesh, NULL);

					// Draw
					pMesh->DrawSubset(0);

					// Release
					pMesh->Release();
				}
				else if(pBox != NULL)
				{
					// Center
					D3DXVECTOR3 vCenter;
					D3DXVec3TransformCoord(&vCenter, &pBox->vCenter, pBox->pMatrix);

					// Point
					D3DXVECTOR3 vPoint[8];
					vPoint[0] = vCenter - pBox->vAxisX * pBox->fWidth;	vPoint[0] = vPoint[0] - pBox->vAxisY * pBox->fHeight;	vPoint[0] = vPoint[0] - pBox->vAxisZ * pBox->fDepth;
					vPoint[1] = vCenter - pBox->vAxisX * pBox->fWidth;	vPoint[1] = vPoint[1] + pBox->vAxisY * pBox->fHeight;	vPoint[1] = vPoint[1] - pBox->vAxisZ * pBox->fDepth;
					vPoint[2] = vCenter + pBox->vAxisX * pBox->fWidth;	vPoint[2] = vPoint[2] + pBox->vAxisY * pBox->fHeight;	vPoint[2] = vPoint[2] - pBox->vAxisZ * pBox->fDepth;
					vPoint[3] = vCenter + pBox->vAxisX * pBox->fWidth;	vPoint[3] = vPoint[3] - pBox->vAxisY * pBox->fHeight;	vPoint[3] = vPoint[3] - pBox->vAxisZ * pBox->fDepth;

					vPoint[4] = vCenter - pBox->vAxisX * pBox->fWidth;	vPoint[4] = vPoint[4] - pBox->vAxisY * pBox->fHeight;	vPoint[4] = vPoint[4] + pBox->vAxisZ * pBox->fDepth;
					vPoint[5] = vCenter - pBox->vAxisX * pBox->fWidth;	vPoint[5] = vPoint[5] + pBox->vAxisY * pBox->fHeight;	vPoint[5] = vPoint[5] + pBox->vAxisZ * pBox->fDepth;
					vPoint[6] = vCenter + pBox->vAxisX * pBox->fWidth;	vPoint[6] = vPoint[6] + pBox->vAxisY * pBox->fHeight;	vPoint[6] = vPoint[6] + pBox->vAxisZ * pBox->fDepth;
					vPoint[7] = vCenter + pBox->vAxisX * pBox->fWidth;	vPoint[7] = vPoint[7] - pBox->vAxisY * pBox->fHeight;	vPoint[7] = vPoint[7] + pBox->vAxisZ * pBox->fDepth;

					// CreateLine
					LPD3DXLINE pLine;
					D3DXCreateLine(CDeviceMgr::GetInstance()->GetDevice(), &pLine);

					// Draw
					pLine->SetWidth(2.0f);
					pLine->Begin();
					pLine->DrawTransform(vPoint, 8, CCameraMgr::GetInstance()->GetViewProj(), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
					pLine->End();
					pLine->Release();
				}
			}
		}
	}

	if(CSettingMgr::GetInstance()->GetGameMode() & GAME_MODE_COLLISION_BOX)
	{
		for(int i = 0; i < COLL_TYPE_END; ++i)
		{
			for(size_t j = 0; j < m_ObjectVec[i].size(); ++j)
			{
				// CollisionCom
				CCollisionCom* pCollisionCom = (CCollisionCom*)m_ObjectVec[i][j]->GetComponent(COM_TYPE_COLLISION);

				for(size_t k = 0; k < pCollisionCom->m_CollisionVec.size(); ++k)
				{
					// Collision
					Collision* pCollision = pCollisionCom->m_CollisionVec[k];

					// Center
					D3DXVECTOR3 vCenter;
					D3DXVec3TransformCoord(&vCenter, &pCollision->vCenter, pCollision->pMatrix);

					// Point
					D3DXVECTOR3 vPoint[8];
					vPoint[0] = vCenter - pCollision->vAxisX * pCollision->fWidth;	vPoint[0] = vPoint[0] - pCollision->vAxisY * pCollision->fHeight;	vPoint[0] = vPoint[0] - pCollision->vAxisZ * pCollision->fDepth;
					vPoint[1] = vCenter - pCollision->vAxisX * pCollision->fWidth;	vPoint[1] = vPoint[1] + pCollision->vAxisY * pCollision->fHeight;	vPoint[1] = vPoint[1] - pCollision->vAxisZ * pCollision->fDepth;
					vPoint[2] = vCenter + pCollision->vAxisX * pCollision->fWidth;	vPoint[2] = vPoint[2] + pCollision->vAxisY * pCollision->fHeight;	vPoint[2] = vPoint[2] - pCollision->vAxisZ * pCollision->fDepth;
					vPoint[3] = vCenter + pCollision->vAxisX * pCollision->fWidth;	vPoint[3] = vPoint[3] - pCollision->vAxisY * pCollision->fHeight;	vPoint[3] = vPoint[3] - pCollision->vAxisZ * pCollision->fDepth;

					vPoint[4] = vCenter - pCollision->vAxisX * pCollision->fWidth;	vPoint[4] = vPoint[4] - pCollision->vAxisY * pCollision->fHeight;	vPoint[4] = vPoint[4] + pCollision->vAxisZ * pCollision->fDepth;
					vPoint[5] = vCenter - pCollision->vAxisX * pCollision->fWidth;	vPoint[5] = vPoint[5] + pCollision->vAxisY * pCollision->fHeight;	vPoint[5] = vPoint[5] + pCollision->vAxisZ * pCollision->fDepth;
					vPoint[6] = vCenter + pCollision->vAxisX * pCollision->fWidth;	vPoint[6] = vPoint[6] + pCollision->vAxisY * pCollision->fHeight;	vPoint[6] = vPoint[6] + pCollision->vAxisZ * pCollision->fDepth;
					vPoint[7] = vCenter + pCollision->vAxisX * pCollision->fWidth;	vPoint[7] = vPoint[7] - pCollision->vAxisY * pCollision->fHeight;	vPoint[7] = vPoint[7] + pCollision->vAxisZ * pCollision->fDepth;

					// CreateLine
					LPD3DXLINE pLine;
					D3DXCreateLine(CDeviceMgr::GetInstance()->GetDevice(), &pLine);

					// Draw
					pLine->SetWidth(2.0f);
					pLine->Begin();
					pLine->DrawTransform(vPoint, 8, CCameraMgr::GetInstance()->GetViewProj(), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
					pLine->End();
					pLine->Release();
				}
			}
		}
	}
}

void CCollisionMgr::Release()
{
}

void CCollisionMgr::AddObject(COLL_TYPE _eCollType, CObject* _pObject)
{
	m_ObjectVec[_eCollType].push_back(_pObject);
}

void CCollisionMgr::RemoveObject(COLL_TYPE _eCollType, CObject* _pObject)
{
	for(size_t i = 0; i < m_ObjectVec[_eCollType].size(); ++i)
	{
		if(m_ObjectVec[_eCollType][i] == _pObject)
		{
			m_ObjectVec[_eCollType][i] = m_ObjectVec[_eCollType][m_ObjectVec[_eCollType].size() - 1];
			m_ObjectVec[_eCollType].pop_back();
		}
	}
}

void CCollisionMgr::PlayerToMonster(CObject* _pPlayer, CObject* _pMonster)
{
	// Center
	D3DXVECTOR3 vPlayerCenter;
	D3DXVECTOR3 vMonsterCenter;

	// Sphere
	Sphere* pPlayerSphere;
	Sphere* pMonsterSphere;

	// CollisionCom
	CCollisionCom* pPlayerCollisionCom = (CCollisionCom*)_pPlayer->GetComponent(COM_TYPE_COLLISION);
	CCollisionCom* pMonsterCollisionCom = (CCollisionCom*)_pMonster->GetComponent(COM_TYPE_COLLISION);

	// CheckSphere
	pPlayerSphere = pPlayerCollisionCom->m_pCheckSphere;
	pMonsterSphere = pMonsterCollisionCom->m_pCheckSphere;

	D3DXVec3TransformCoord(&vPlayerCenter, &pPlayerSphere->vCenter, pPlayerSphere->pMatrix);
	D3DXVec3TransformCoord(&vMonsterCenter, &pMonsterSphere->vCenter, pMonsterSphere->pMatrix);

	vPlayerCenter += pPlayerCollisionCom->m_vPushed;
	vMonsterCenter += pMonsterCollisionCom->m_vPushed;

	if(CircleToCircle(&D3DXVECTOR2(vPlayerCenter.x, vPlayerCenter.z), pPlayerSphere->fRadius, &D3DXVECTOR2(vMonsterCenter.x, vMonsterCenter.z), pMonsterSphere->fRadius) == false)
		return;

	// CollisionShpere
	pPlayerSphere = pPlayerCollisionCom->m_pCollisionSphere;
	pMonsterSphere = pMonsterCollisionCom->m_pCollisionSphere;

	D3DXVec3TransformCoord(&vPlayerCenter, &pPlayerSphere->vCenter, pPlayerSphere->pMatrix);
	D3DXVec3TransformCoord(&vMonsterCenter, &pMonsterSphere->vCenter, pMonsterSphere->pMatrix);

	vPlayerCenter += pPlayerCollisionCom->m_vPushed;
	vMonsterCenter += pMonsterCollisionCom->m_vPushed;

	if(CircleToCircle(&D3DXVECTOR2(vPlayerCenter.x, vPlayerCenter.z), pPlayerSphere->fRadius, &D3DXVECTOR2(vMonsterCenter.x, vMonsterCenter.z), pMonsterSphere->fRadius))
	{
		// PathFindCom
		CPathFindCom* pPlayerPathFindCom = (CPathFindCom*)_pPlayer->GetComponent(COM_TYPE_PATH_FIND);

		D3DXVECTOR3 vMonToPlayer = vPlayerCenter - vMonsterCenter;
		if(!Equals(vMonToPlayer.x, 0.0f, MIN_EPSILON) || !Equals(vMonToPlayer.z, 0.0f, MIN_EPSILON))
		{
			// MonToPlayer
			vMonToPlayer.y = 0.0f;
			D3DXVec3Normalize(&vMonToPlayer, &vMonToPlayer);

			// TransformCom
			CTransformCom* pTransformCom = (CTransformCom*)_pPlayer->GetComponent(COM_TYPE_TRANSFORM);

			// NextPos
			D3DXVECTOR3 vNextPos = vMonsterCenter + vMonToPlayer * (pPlayerSphere->fRadius + pMonsterSphere->fRadius + MIN_EPSILON);

			// Solution
			CNaviCell* pNextCell;
			CPathFindMgr::GetInstance()->Solution(&pTransformCom->m_vPos, pPlayerPathFindCom->m_pCell, &vNextPos, &pNextCell);

			// Pushed
			pPlayerCollisionCom->m_vPushed += vNextPos - pTransformCom->m_vPos;

			// Pos
			pTransformCom->m_vPos = vNextPos;
			pPlayerPathFindCom->m_pCell = pNextCell;
		}
	}

	// Collision
	Collision* pPlayerCollision;
	Collision* pMonsterCollision;

	// Variable
	D3DXVECTOR3 vAtoB, vAtoE1, vAtoE2, vBtoE1, vBtoE2;
	float fAtoB, fAtoE, fBtoE;
	bool bPass;

	// Attack Of Player
	for(size_t i = 0; i < pPlayerCollisionCom->m_CollisionVec.size(); ++i)
	{
		// PlayerCollision
		pPlayerCollision = pPlayerCollisionCom->m_CollisionVec[i];

		if((pPlayerCollision->dwType & COLLISION_ATTACK) == 0)
			continue;

		bPass = false;
		for(size_t j = 0; j < pPlayerCollision->ExceptVec.size(); ++j)
		{
			if(pPlayerCollision->ExceptVec[j] == _pMonster)
			{
				bPass = true;
				break;
			}
		}

		if(bPass)
			continue;

		// PlayerCenter
		D3DXVec3TransformCoord(&vPlayerCenter, &pPlayerCollision->vCenter, pPlayerCollision->pMatrix);

		for(size_t j = 0; j < pMonsterCollisionCom->m_CollisionVec.size(); ++j)
		{
			// MonsterCollision
			pMonsterCollision = pMonsterCollisionCom->m_CollisionVec[j];

			if((pMonsterCollision->dwType & COLLISION_DAMAGE) == 0)
				continue;

			// MonsterCenter
			D3DXVec3TransformCoord(&vMonsterCenter, &pMonsterCollision->vCenter, pMonsterCollision->pMatrix);

			// Vector
			vAtoB = vMonsterCenter - vPlayerCenter;
			vAtoE1 = pPlayerCollision->vAxisZ * pPlayerCollision->fDepth;
			vAtoE2 = pPlayerCollision->vAxisY * pPlayerCollision->fHeight + pPlayerCollision->vAxisX * pPlayerCollision->fWidth;
			vBtoE1 = pMonsterCollision->vAxisZ * pMonsterCollision->fDepth;
			vBtoE2 = pMonsterCollision->vAxisY * pMonsterCollision->fHeight + pMonsterCollision->vAxisX * pMonsterCollision->fWidth;

			// A의 X축 투영
			fAtoB = abs(D3DXVec3Dot(&pPlayerCollision->vAxisX, &vAtoB));
			fAtoE = abs(D3DXVec3Dot(&pPlayerCollision->vAxisX, &vAtoE1)) + abs(D3DXVec3Dot(&pPlayerCollision->vAxisX, &vAtoE2));
			fBtoE = abs(D3DXVec3Dot(&pPlayerCollision->vAxisX, &vBtoE1)) + abs(D3DXVec3Dot(&pPlayerCollision->vAxisX, &vBtoE2));

			if(fAtoB > fAtoE + fBtoE)
				continue;

			// A의 Y축 투영
			fAtoB = abs(D3DXVec3Dot(&pPlayerCollision->vAxisY, &vAtoB));
			fAtoE = abs(D3DXVec3Dot(&pPlayerCollision->vAxisY, &vAtoE1)) + abs(D3DXVec3Dot(&pPlayerCollision->vAxisY, &vAtoE2));
			fBtoE = abs(D3DXVec3Dot(&pPlayerCollision->vAxisY, &vBtoE1)) + abs(D3DXVec3Dot(&pPlayerCollision->vAxisY, &vBtoE2));

			if(fAtoB > fAtoE + fBtoE)
				continue;

			// A의 Z축 투영
			fAtoB = abs(D3DXVec3Dot(&pPlayerCollision->vAxisZ, &vAtoB));
			fAtoE = abs(D3DXVec3Dot(&pPlayerCollision->vAxisZ, &vAtoE1)) + abs(D3DXVec3Dot(&pPlayerCollision->vAxisZ, &vAtoE2));
			fBtoE = abs(D3DXVec3Dot(&pPlayerCollision->vAxisZ, &vBtoE1)) + abs(D3DXVec3Dot(&pPlayerCollision->vAxisZ, &vBtoE2));

			if(fAtoB > fAtoE + fBtoE)
				continue;

			// B의 X축 투영
			fAtoB = abs(D3DXVec3Dot(&pMonsterCollision->vAxisX, &vAtoB));
			fAtoE = abs(D3DXVec3Dot(&pMonsterCollision->vAxisX, &vAtoE1)) + abs(D3DXVec3Dot(&pMonsterCollision->vAxisX, &vAtoE2));
			fBtoE = abs(D3DXVec3Dot(&pMonsterCollision->vAxisX, &vBtoE1)) + abs(D3DXVec3Dot(&pMonsterCollision->vAxisX, &vBtoE2));

			if(fAtoB > fAtoE + fBtoE)
				continue;

			// B의 Y축 투영
			fAtoB = abs(D3DXVec3Dot(&pMonsterCollision->vAxisY, &vAtoB));
			fAtoE = abs(D3DXVec3Dot(&pMonsterCollision->vAxisY, &vAtoE1)) + abs(D3DXVec3Dot(&pMonsterCollision->vAxisY, &vAtoE2));
			fBtoE = abs(D3DXVec3Dot(&pMonsterCollision->vAxisY, &vBtoE1)) + abs(D3DXVec3Dot(&pMonsterCollision->vAxisY, &vBtoE2));

			if(fAtoB > fAtoE + fBtoE)
				continue;

			// B의 Z축 투영
			fAtoB = abs(D3DXVec3Dot(&pMonsterCollision->vAxisZ, &vAtoB));
			fAtoE = abs(D3DXVec3Dot(&pMonsterCollision->vAxisZ, &vAtoE1)) + abs(D3DXVec3Dot(&pMonsterCollision->vAxisZ, &vAtoE2));
			fBtoE = abs(D3DXVec3Dot(&pMonsterCollision->vAxisZ, &vBtoE1)) + abs(D3DXVec3Dot(&pMonsterCollision->vAxisZ, &vBtoE2));

			if(fAtoB > fAtoE + fBtoE)
				continue;

			((CMonster*)_pMonster)->Damage((CPlayer*)_pPlayer);
			pPlayerCollision->ExceptVec.push_back(_pMonster);
		}
	}

	// Attack Of Monster
	for(size_t i = 0; i < pMonsterCollisionCom->m_CollisionVec.size(); ++i)
	{
		// MonsterCollision
		pMonsterCollision = pMonsterCollisionCom->m_CollisionVec[i];

		if((pMonsterCollision->dwType & COLLISION_ATTACK) == 0)
			continue;

		bPass = false;
		for(size_t j = 0; j < pMonsterCollision->ExceptVec.size(); ++j)
		{
			if(pMonsterCollision->ExceptVec[j] == _pPlayer)
			{
				bPass = true;
				break;
			}
		}

		if(bPass)
			continue;

		// MonsterCenter
		D3DXVec3TransformCoord(&vMonsterCenter, &pMonsterCollision->vCenter, pMonsterCollision->pMatrix);

		for(size_t j = 0; j < pPlayerCollisionCom->m_CollisionVec.size(); ++j)
		{
			// PlayerCollision
			pPlayerCollision = pPlayerCollisionCom->m_CollisionVec[j];

			if((pPlayerCollision->dwType & COLLISION_DAMAGE) == 0)
				continue;

			// PlayerCenter
			D3DXVec3TransformCoord(&vPlayerCenter, &pPlayerCollision->vCenter, pPlayerCollision->pMatrix);

			// Vector
			vAtoB = vMonsterCenter - vPlayerCenter;
			vAtoE1 = pPlayerCollision->vAxisZ * pPlayerCollision->fDepth;
			vAtoE2 = pPlayerCollision->vAxisY * pPlayerCollision->fHeight + pPlayerCollision->vAxisX * pPlayerCollision->fWidth;
			vBtoE1 = pMonsterCollision->vAxisZ * pMonsterCollision->fDepth;
			vBtoE2 = pMonsterCollision->vAxisY * pMonsterCollision->fHeight + pMonsterCollision->vAxisX * pMonsterCollision->fWidth;

			// A의 X축 투영
			fAtoB = abs(D3DXVec3Dot(&pPlayerCollision->vAxisX, &vAtoB));
			fAtoE = abs(D3DXVec3Dot(&pPlayerCollision->vAxisX, &vAtoE1)) + abs(D3DXVec3Dot(&pPlayerCollision->vAxisX, &vAtoE2));
			fBtoE = abs(D3DXVec3Dot(&pPlayerCollision->vAxisX, &vBtoE1)) + abs(D3DXVec3Dot(&pPlayerCollision->vAxisX, &vBtoE2));

			if(fAtoB > fAtoE + fBtoE)
				continue;

			// A의 Y축 투영
			fAtoB = abs(D3DXVec3Dot(&pPlayerCollision->vAxisY, &vAtoB));
			fAtoE = abs(D3DXVec3Dot(&pPlayerCollision->vAxisY, &vAtoE1)) + abs(D3DXVec3Dot(&pPlayerCollision->vAxisY, &vAtoE2));
			fBtoE = abs(D3DXVec3Dot(&pPlayerCollision->vAxisY, &vBtoE1)) + abs(D3DXVec3Dot(&pPlayerCollision->vAxisY, &vBtoE2));

			if(fAtoB > fAtoE + fBtoE)
				continue;

			// A의 Z축 투영
			fAtoB = abs(D3DXVec3Dot(&pPlayerCollision->vAxisZ, &vAtoB));
			fAtoE = abs(D3DXVec3Dot(&pPlayerCollision->vAxisZ, &vAtoE1)) + abs(D3DXVec3Dot(&pPlayerCollision->vAxisZ, &vAtoE2));
			fBtoE = abs(D3DXVec3Dot(&pPlayerCollision->vAxisZ, &vBtoE1)) + abs(D3DXVec3Dot(&pPlayerCollision->vAxisZ, &vBtoE2));

			if(fAtoB > fAtoE + fBtoE)
				continue;

			// B의 X축 투영
			fAtoB = abs(D3DXVec3Dot(&pMonsterCollision->vAxisX, &vAtoB));
			fAtoE = abs(D3DXVec3Dot(&pMonsterCollision->vAxisX, &vAtoE1)) + abs(D3DXVec3Dot(&pMonsterCollision->vAxisX, &vAtoE2));
			fBtoE = abs(D3DXVec3Dot(&pMonsterCollision->vAxisX, &vBtoE1)) + abs(D3DXVec3Dot(&pMonsterCollision->vAxisX, &vBtoE2));

			if(fAtoB > fAtoE + fBtoE)
				continue;

			// B의 Y축 투영
			fAtoB = abs(D3DXVec3Dot(&pMonsterCollision->vAxisY, &vAtoB));
			fAtoE = abs(D3DXVec3Dot(&pMonsterCollision->vAxisY, &vAtoE1)) + abs(D3DXVec3Dot(&pMonsterCollision->vAxisY, &vAtoE2));
			fBtoE = abs(D3DXVec3Dot(&pMonsterCollision->vAxisY, &vBtoE1)) + abs(D3DXVec3Dot(&pMonsterCollision->vAxisY, &vBtoE2));

			if(fAtoB > fAtoE + fBtoE)
				continue;

			// B의 Z축 투영
			fAtoB = abs(D3DXVec3Dot(&pMonsterCollision->vAxisZ, &vAtoB));
			fAtoE = abs(D3DXVec3Dot(&pMonsterCollision->vAxisZ, &vAtoE1)) + abs(D3DXVec3Dot(&pMonsterCollision->vAxisZ, &vAtoE2));
			fBtoE = abs(D3DXVec3Dot(&pMonsterCollision->vAxisZ, &vBtoE1)) + abs(D3DXVec3Dot(&pMonsterCollision->vAxisZ, &vBtoE2));

			if(fAtoB > fAtoE + fBtoE)
				continue;

			((CPlayer*)_pPlayer)->Damage((CMonster*)_pMonster);
			pMonsterCollision->ExceptVec.push_back(_pPlayer);
		}
	}
}

void CCollisionMgr::MonsterToMonster(CObject* _pMonsterA, CObject* _pMonsterB)
{
	// Center
	D3DXVECTOR3 vMonsterCenterA;
	D3DXVECTOR3 vMonsterCenterB;

	// Sphere
	Sphere* pMonsterSphereA;
	Sphere* pMonsterSphereB;

	// CollisionCom
	CCollisionCom* pMonsterCollisionComA = (CCollisionCom*)_pMonsterA->GetComponent(COM_TYPE_COLLISION);
	CCollisionCom* pMonsterCollisionComB = (CCollisionCom*)_pMonsterB->GetComponent(COM_TYPE_COLLISION);

	// CheckSphere
	pMonsterSphereA = pMonsterCollisionComA->m_pCheckSphere;
	pMonsterSphereB = pMonsterCollisionComB->m_pCheckSphere;

	D3DXVec3TransformCoord(&vMonsterCenterA, &pMonsterSphereA->vCenter, pMonsterSphereA->pMatrix);
	D3DXVec3TransformCoord(&vMonsterCenterB, &pMonsterSphereB->vCenter, pMonsterSphereB->pMatrix);

	vMonsterCenterA += pMonsterCollisionComA->m_vPushed;
	vMonsterCenterB += pMonsterCollisionComB->m_vPushed;

	if(CircleToCircle(&D3DXVECTOR2(vMonsterCenterA.x, vMonsterCenterA.z), pMonsterSphereA->fRadius, &D3DXVECTOR2(vMonsterCenterB.x, vMonsterCenterB.z), pMonsterSphereB->fRadius) == false)
		return;

	// CollisionShpere
	pMonsterSphereA = pMonsterCollisionComA->m_pCollisionSphere;
	pMonsterSphereB = pMonsterCollisionComB->m_pCollisionSphere;

	D3DXVec3TransformCoord(&vMonsterCenterA, &pMonsterSphereA->vCenter, pMonsterSphereA->pMatrix);
	D3DXVec3TransformCoord(&vMonsterCenterB, &pMonsterSphereB->vCenter, pMonsterSphereB->pMatrix);

	vMonsterCenterA += pMonsterCollisionComA->m_vPushed;
	vMonsterCenterB += pMonsterCollisionComB->m_vPushed;

	if(CircleToCircle(&D3DXVECTOR2(vMonsterCenterA.x, vMonsterCenterA.z), pMonsterSphereA->fRadius, &D3DXVECTOR2(vMonsterCenterB.x, vMonsterCenterB.z), pMonsterSphereB->fRadius))
	{
		// PathFindCom
		CPathFindCom* pMonsterPathFindComA = (CPathFindCom*)_pMonsterA->GetComponent(COM_TYPE_PATH_FIND);
		CPathFindCom* pMonsterPathFindComB = (CPathFindCom*)_pMonsterB->GetComponent(COM_TYPE_PATH_FIND);
		CNaviCell* pNextCell;

		if(pMonsterPathFindComA->m_bEnable && pMonsterPathFindComB->m_bEnable)
		{
			if(D3DXVec3Length(&pMonsterPathFindComA->m_vDir) > D3DXVec3Length(&pMonsterPathFindComB->m_vDir))
			{
				D3DXVECTOR3 vBToA = vMonsterCenterA - vMonsterCenterB;
				if(!Equals(vBToA.x, 0.0f, MIN_EPSILON) || !Equals(vBToA.z, 0.0f, MIN_EPSILON))
				{
					// BToA
					vBToA.y = 0.0f;
					D3DXVec3Normalize(&vBToA, &vBToA);

					// TransformCom
					CTransformCom* pTransformCom = (CTransformCom*)_pMonsterA->GetComponent(COM_TYPE_TRANSFORM);

					// NextPos
					D3DXVECTOR3 vNextPos = vMonsterCenterB + vBToA * (pMonsterSphereA->fRadius + pMonsterSphereB->fRadius + MAX_EPSILON * 2.0f);

					// Solution
					CPathFindMgr::GetInstance()->Solution(&pTransformCom->m_vPos, pMonsterPathFindComA->m_pCell, &vNextPos, &pNextCell);

					// Pushed
					pMonsterCollisionComA->m_vPushed += vNextPos - pTransformCom->m_vPos;

					// Pos
					pTransformCom->m_vPos = vNextPos;
					pMonsterPathFindComA->m_pCell = pNextCell;
				}
			}
			else
			{
				D3DXVECTOR3 vAToB = vMonsterCenterB - vMonsterCenterA;
				if(!Equals(vAToB.x, 0.0f, MIN_EPSILON) || !Equals(vAToB.z, 0.0f, MIN_EPSILON))
				{
					// AToB
					vAToB.y = 0.0f;
					D3DXVec3Normalize(&vAToB, &vAToB);

					// TransformCom
					CTransformCom* pTransformCom = (CTransformCom*)_pMonsterB->GetComponent(COM_TYPE_TRANSFORM);

					// NextPos
					D3DXVECTOR3 vNextPos = vMonsterCenterA + vAToB * (pMonsterSphereA->fRadius + pMonsterSphereB->fRadius + MAX_EPSILON * 2.0f);

					// Solution
					CPathFindMgr::GetInstance()->Solution(&pTransformCom->m_vPos, pMonsterPathFindComB->m_pCell, &vNextPos, &pNextCell);

					// Pushed
					pMonsterCollisionComB->m_vPushed += vNextPos - pTransformCom->m_vPos;

					// Pos
					pTransformCom->m_vPos = vNextPos;
					pMonsterPathFindComB->m_pCell = pNextCell;
				}
			}
		}
		else if(pMonsterPathFindComA->m_bEnable)
		{
			D3DXVECTOR3 vBToA = vMonsterCenterA - vMonsterCenterB;
			if(!Equals(vBToA.x, 0.0f, MIN_EPSILON) || !Equals(vBToA.z, 0.0f, MIN_EPSILON))
			{
				// BToA
				vBToA.y = 0.0f;
				D3DXVec3Normalize(&vBToA, &vBToA);

				// TransformCom
				CTransformCom* pTransformCom = (CTransformCom*)_pMonsterA->GetComponent(COM_TYPE_TRANSFORM);

				// NextPos
				D3DXVECTOR3 vNextPos = vMonsterCenterB + vBToA * (pMonsterSphereA->fRadius + pMonsterSphereB->fRadius + MAX_EPSILON * 2.0f);

				// Solution
				CPathFindMgr::GetInstance()->Solution(&pTransformCom->m_vPos, pMonsterPathFindComA->m_pCell, &vNextPos, &pNextCell);

				// Pushed
				pMonsterCollisionComA->m_vPushed += vNextPos - pTransformCom->m_vPos;

				// Pos
				pTransformCom->m_vPos = vNextPos;
				pMonsterPathFindComA->m_pCell = pNextCell;
			}
		}
		else if(pMonsterPathFindComB->m_bEnable)
		{
			D3DXVECTOR3 vAToB = vMonsterCenterB - vMonsterCenterA;
			if(!Equals(vAToB.x, 0.0f, MIN_EPSILON) || !Equals(vAToB.z, 0.0f, MIN_EPSILON))
			{
				// AToB
				vAToB.y = 0.0f;
				D3DXVec3Normalize(&vAToB, &vAToB);

				// TransformCom
				CTransformCom* pTransformCom = (CTransformCom*)_pMonsterB->GetComponent(COM_TYPE_TRANSFORM);

				// NextPos
				D3DXVECTOR3 vNextPos = vMonsterCenterA + vAToB * (pMonsterSphereA->fRadius + pMonsterSphereB->fRadius + MAX_EPSILON * 2.0f);

				// Solution
				CPathFindMgr::GetInstance()->Solution(&pTransformCom->m_vPos, pMonsterPathFindComB->m_pCell, &vNextPos, &pNextCell);

				// Pushed
				pMonsterCollisionComB->m_vPushed += vNextPos - pTransformCom->m_vPos;

				// Pos
				pTransformCom->m_vPos = vNextPos;
				pMonsterPathFindComB->m_pCell = pNextCell;
			}
		}
	}
}

void CCollisionMgr::PlayerToEffect(CObject* _pPlayer, CObject* _pEffect)
{
	// CollisionCom
	CCollisionCom* pPlayerCollisionCom = (CCollisionCom*)_pPlayer->GetComponent(COM_TYPE_COLLISION);
	CCollisionCom* pEffectCollisionCom = (CCollisionCom*)_pEffect->GetComponent(COM_TYPE_COLLISION);

	// Shpere
	Sphere* pPlayerSphere = pPlayerCollisionCom->m_pCheckSphere;
	Sphere* pEffectSphere = pEffectCollisionCom->m_pCheckSphere;

	// Center
	D3DXVECTOR3 vPlayerCenter;
	D3DXVECTOR3 vEffectCenter;

	D3DXVec3TransformCoord(&vPlayerCenter, &pPlayerSphere->vCenter, pPlayerSphere->pMatrix);
	D3DXVec3TransformCoord(&vEffectCenter, &pEffectSphere->vCenter, pEffectSphere->pMatrix);

	vPlayerCenter += pPlayerCollisionCom->m_vPushed;
	vEffectCenter += pEffectCollisionCom->m_vPushed;

	if(CircleToCircle(&D3DXVECTOR2(vPlayerCenter.x, vPlayerCenter.z), pPlayerSphere->fRadius, &D3DXVECTOR2(vEffectCenter.x, vEffectCenter.z), pEffectSphere->fRadius) == false)
		return;

	D3DXVECTOR3 vLB, vRT, vLBEx, vRTEx, vCorner;
	Collision* pPlayerCollision;
	float fTemp;
	bool bPass;

	// Attack of Effect
	for(size_t i = 0; i < pPlayerCollisionCom->m_CollisionVec.size(); ++i)
	{
		// PlayerCollision
		pPlayerCollision = pPlayerCollisionCom->m_CollisionVec[i];
		if((pPlayerCollision->dwType & COLLISION_DAMAGE) == false)
			continue;

		bPass = false;
		for(size_t j = 0; j < pEffectSphere->ExceptVec.size(); ++j)
		{
			if(pEffectSphere->ExceptVec[j] == _pPlayer)
			{
				bPass = true;
				break;
			}
		}

		if(bPass)
			continue;

		// PlayerCenter
		D3DXVec3TransformCoord(&vPlayerCenter, &pPlayerCollision->vCenter, pPlayerCollision->pMatrix);
		vPlayerCenter += pPlayerCollisionCom->m_vPushed;

		// LB
		vLB = vPlayerCenter -
			pPlayerCollision->vAxisX * pPlayerCollision->fWidth / 2.0f -
			pPlayerCollision->vAxisY * pPlayerCollision->fHeight / 2.0f -
			pPlayerCollision->vAxisZ * pPlayerCollision->fDepth / 2.0f;

		// RT
		vRT = vPlayerCenter +
			pPlayerCollision->vAxisX * pPlayerCollision->fWidth / 2.0f +
			pPlayerCollision->vAxisY * pPlayerCollision->fHeight / 2.0f +
			pPlayerCollision->vAxisZ * pPlayerCollision->fDepth / 2.0f;

		// Sort
		if(vLB.x > vRT.x) { fTemp = vLB.x; vLB.x = vRT.x; vRT.x = fTemp; }
		if(vLB.y > vRT.y) { fTemp = vLB.y; vLB.y = vRT.y; vRT.y = fTemp; }
		if(vLB.z > vRT.z) { fTemp = vLB.z; vLB.z = vRT.z; vRT.z = fTemp; }

		if((vLB.x <= vEffectCenter.x && vEffectCenter.x <= vRT.x) || (vLB.y <= vEffectCenter.y && vEffectCenter.y <= vRT.y) || (vLB.z <= vEffectCenter.z && vEffectCenter.z <= vRT.z))
		{
			vLBEx.x = vLB.x - pEffectSphere->fRadius;
			vLBEx.y = vLB.y - pEffectSphere->fRadius;
			vLBEx.z = vLB.z - pEffectSphere->fRadius;

			vRTEx.x = vRT.x + pEffectSphere->fRadius;
			vRTEx.y = vRT.y + pEffectSphere->fRadius;
			vRTEx.z = vRT.z + pEffectSphere->fRadius;

			if(vLBEx.x <= vEffectCenter.x && vEffectCenter.x <= vRTEx.x && vLBEx.y <= vEffectCenter.y && vEffectCenter.y <= vRTEx.y && vLBEx.z <= vEffectCenter.z && vEffectCenter.z <= vRTEx.z)
			{
				((CEffect*)_pEffect)->AddCnt();
				((CPlayer*)_pPlayer)->Damage((CEffect*)_pEffect);
				pEffectSphere->ExceptVec.push_back(_pPlayer);
				return;
			}
		}

		vCorner.x = vLB.x;	vCorner.y = vLB.y;	vCorner.z = vLB.z;
		if(PointInSphere(&vCorner, &vEffectCenter, pEffectSphere->fRadius))
		{
			((CEffect*)_pEffect)->AddCnt();
			((CPlayer*)_pPlayer)->Damage((CEffect*)_pEffect);
			pEffectSphere->ExceptVec.push_back(_pPlayer);
			return;
		}

		vCorner.x = vLB.x;	vCorner.y = vRT.y;	vCorner.z = vLB.z;
		if(PointInSphere(&vCorner, &vEffectCenter, pEffectSphere->fRadius))
		{
			((CEffect*)_pEffect)->AddCnt();
			((CPlayer*)_pPlayer)->Damage((CEffect*)_pEffect);
			pEffectSphere->ExceptVec.push_back(_pPlayer);
			return;
		}

		vCorner.x = vRT.x;	vCorner.y = vRT.y;	vCorner.z = vLB.z;
		if(PointInSphere(&vCorner, &vEffectCenter, pEffectSphere->fRadius))
		{
			((CEffect*)_pEffect)->AddCnt();
			((CPlayer*)_pPlayer)->Damage((CEffect*)_pEffect);
			pEffectSphere->ExceptVec.push_back(_pPlayer);
			return;
		}

		vCorner.x = vRT.x;	vCorner.y = vLB.y;	vCorner.z = vLB.z;
		if(PointInSphere(&vCorner, &vEffectCenter, pEffectSphere->fRadius))
		{
			((CEffect*)_pEffect)->AddCnt();
			((CPlayer*)_pPlayer)->Damage((CEffect*)_pEffect);
			pEffectSphere->ExceptVec.push_back(_pPlayer);
			return;
		}

		vCorner.x = vLB.x;	vCorner.y = vLB.y;	vCorner.z = vRT.z;
		if(PointInSphere(&vCorner, &vEffectCenter, pEffectSphere->fRadius))
		{
			((CEffect*)_pEffect)->AddCnt();
			((CPlayer*)_pPlayer)->Damage((CEffect*)_pEffect);
			pEffectSphere->ExceptVec.push_back(_pPlayer);
			return;
		}

		vCorner.x = vLB.x;	vCorner.y = vRT.y;	vCorner.z = vRT.z;
		if(PointInSphere(&vCorner, &vEffectCenter, pEffectSphere->fRadius))
		{
			((CEffect*)_pEffect)->AddCnt();
			((CPlayer*)_pPlayer)->Damage((CEffect*)_pEffect);
			pEffectSphere->ExceptVec.push_back(_pPlayer);
			return;
		}

		vCorner.x = vRT.x;	vCorner.y = vRT.y;	vCorner.z = vRT.z;
		if(PointInSphere(&vCorner, &vEffectCenter, pEffectSphere->fRadius))
		{
			((CEffect*)_pEffect)->AddCnt();
			((CPlayer*)_pPlayer)->Damage((CEffect*)_pEffect);
			pEffectSphere->ExceptVec.push_back(_pPlayer);
			return;
		}

		vCorner.x = vRT.x;	vCorner.y = vLB.y;	vCorner.z = vRT.z;
		if(PointInSphere(&vCorner, &vEffectCenter, pEffectSphere->fRadius))
		{
			((CEffect*)_pEffect)->AddCnt();
			((CPlayer*)_pPlayer)->Damage((CEffect*)_pEffect);
			pEffectSphere->ExceptVec.push_back(_pPlayer);
			return;
		}
	}
}

void CCollisionMgr::MonsterToEffect(CObject* _pMonster, CObject* _pEffect)
{
	// CollisionCom
	CCollisionCom* pMonsterCollisionCom = (CCollisionCom*)_pMonster->GetComponent(COM_TYPE_COLLISION);
	CCollisionCom* pEffectCollisionCom = (CCollisionCom*)_pEffect->GetComponent(COM_TYPE_COLLISION);

	// Shpere
	Sphere* pMonsterSphere = pMonsterCollisionCom->m_pCheckSphere;
	Sphere* pEffectSphere = pEffectCollisionCom->m_pCheckSphere;

	// Center
	D3DXVECTOR3 vMonsterCenter;
	D3DXVECTOR3 vEffectCenter;

	D3DXVec3TransformCoord(&vMonsterCenter, &pMonsterSphere->vCenter, pMonsterSphere->pMatrix);
	D3DXVec3TransformCoord(&vEffectCenter, &pEffectSphere->vCenter, pEffectSphere->pMatrix);

	vMonsterCenter += pMonsterCollisionCom->m_vPushed;
	vEffectCenter += pEffectCollisionCom->m_vPushed;

	if(CircleToCircle(&D3DXVECTOR2(vMonsterCenter.x, vMonsterCenter.z), pMonsterSphere->fRadius, &D3DXVECTOR2(vEffectCenter.x, vEffectCenter.z), pEffectSphere->fRadius) == false)
		return;

	D3DXVECTOR3 vLB, vRT, vLBEx, vRTEx, vCorner;
	Collision* pMonsterCollision;
	float fTemp;
	bool bPass;

	for(size_t i = 0; i < pMonsterCollisionCom->m_CollisionVec.size(); ++i)
	{
		// MonsterCollision
		pMonsterCollision = pMonsterCollisionCom->m_CollisionVec[i];
		if((pMonsterCollision->dwType & COLLISION_DAMAGE) == false)
			continue;

		bPass = false;
		for(size_t j = 0; j < pEffectSphere->ExceptVec.size(); ++j)
		{
			if(pEffectSphere->ExceptVec[j] == _pMonster)
			{
				bPass = true;
				break;
			}
		}

		if(bPass)
			continue;

		// MonsterCenter
		D3DXVec3TransformCoord(&vMonsterCenter, &pMonsterCollision->vCenter, pMonsterCollision->pMatrix);
		vMonsterCenter += pMonsterCollisionCom->m_vPushed;

		// LB
		vLB = vMonsterCenter -
			pMonsterCollision->vAxisX * pMonsterCollision->fWidth / 2.0f -
			pMonsterCollision->vAxisY * pMonsterCollision->fHeight / 2.0f -
			pMonsterCollision->vAxisZ * pMonsterCollision->fDepth / 2.0f;

		// RT
		vRT = vMonsterCenter +
			pMonsterCollision->vAxisX * pMonsterCollision->fWidth / 2.0f +
			pMonsterCollision->vAxisY * pMonsterCollision->fHeight / 2.0f +
			pMonsterCollision->vAxisZ * pMonsterCollision->fDepth / 2.0f;

		// Sort
		if(vLB.x > vRT.x) { fTemp = vLB.x; vLB.x = vRT.x; vRT.x = fTemp; }
		if(vLB.y > vRT.y) { fTemp = vLB.y; vLB.y = vRT.y; vRT.y = fTemp; }
		if(vLB.z > vRT.z) { fTemp = vLB.z; vLB.z = vRT.z; vRT.z = fTemp; }

		if((vLB.x <= vEffectCenter.x && vEffectCenter.x <= vRT.x) || (vLB.y <= vEffectCenter.y && vEffectCenter.y <= vRT.y) || (vLB.z <= vEffectCenter.z && vEffectCenter.z <= vRT.z))
		{
			vLBEx.x = vLB.x - pEffectSphere->fRadius;
			vLBEx.y = vLB.y - pEffectSphere->fRadius;
			vLBEx.z = vLB.z - pEffectSphere->fRadius;

			vRTEx.x = vRT.x + pEffectSphere->fRadius;
			vRTEx.y = vRT.y + pEffectSphere->fRadius;
			vRTEx.z = vRT.z + pEffectSphere->fRadius;

			if(vLBEx.x <= vEffectCenter.x && vEffectCenter.x <= vRTEx.x && vLBEx.y <= vEffectCenter.y && vEffectCenter.y <= vRTEx.y && vLBEx.z <= vEffectCenter.z && vEffectCenter.z <= vRTEx.z)
			{
				((CEffect*)_pEffect)->AddCnt();
				((CMonster*)_pMonster)->Damage((CEffect*)_pEffect);
				pEffectSphere->ExceptVec.push_back(_pMonster);
				return;
			}
		}

		vCorner.x = vLB.x;	vCorner.y = vLB.y;	vCorner.z = vLB.z;
		if(PointInSphere(&vCorner, &vEffectCenter, pEffectSphere->fRadius))
		{
			((CEffect*)_pEffect)->AddCnt();
			((CMonster*)_pMonster)->Damage((CEffect*)_pEffect);
			pEffectSphere->ExceptVec.push_back(_pMonster);
			return;
		}

		vCorner.x = vLB.x;	vCorner.y = vRT.y;	vCorner.z = vLB.z;
		if(PointInSphere(&vCorner, &vEffectCenter, pEffectSphere->fRadius))
		{
			((CEffect*)_pEffect)->AddCnt();
			((CMonster*)_pMonster)->Damage((CEffect*)_pEffect);
			pEffectSphere->ExceptVec.push_back(_pMonster);
			return;
		}

		vCorner.x = vRT.x;	vCorner.y = vRT.y;	vCorner.z = vLB.z;
		if(PointInSphere(&vCorner, &vEffectCenter, pEffectSphere->fRadius))
		{
			((CEffect*)_pEffect)->AddCnt();
			((CMonster*)_pMonster)->Damage((CEffect*)_pEffect);
			pEffectSphere->ExceptVec.push_back(_pMonster);
			return;
		}

		vCorner.x = vRT.x;	vCorner.y = vLB.y;	vCorner.z = vLB.z;
		if(PointInSphere(&vCorner, &vEffectCenter, pEffectSphere->fRadius))
		{
			((CEffect*)_pEffect)->AddCnt();
			((CMonster*)_pMonster)->Damage((CEffect*)_pEffect);
			pEffectSphere->ExceptVec.push_back(_pMonster);
			return;
		}

		vCorner.x = vLB.x;	vCorner.y = vLB.y;	vCorner.z = vRT.z;
		if(PointInSphere(&vCorner, &vEffectCenter, pEffectSphere->fRadius))
		{
			((CEffect*)_pEffect)->AddCnt();
			((CMonster*)_pMonster)->Damage((CEffect*)_pEffect);
			pEffectSphere->ExceptVec.push_back(_pMonster);
			return;
		}

		vCorner.x = vLB.x;	vCorner.y = vRT.y;	vCorner.z = vRT.z;
		if(PointInSphere(&vCorner, &vEffectCenter, pEffectSphere->fRadius))
		{
			((CEffect*)_pEffect)->AddCnt();
			((CMonster*)_pMonster)->Damage((CEffect*)_pEffect);
			pEffectSphere->ExceptVec.push_back(_pMonster);
			return;
		}

		vCorner.x = vRT.x;	vCorner.y = vRT.y;	vCorner.z = vRT.z;
		if(PointInSphere(&vCorner, &vEffectCenter, pEffectSphere->fRadius))
		{
			((CEffect*)_pEffect)->AddCnt();
			((CMonster*)_pMonster)->Damage((CEffect*)_pEffect);
			pEffectSphere->ExceptVec.push_back(_pMonster);
			return;
		}

		vCorner.x = vRT.x;	vCorner.y = vLB.y;	vCorner.z = vRT.z;
		if(PointInSphere(&vCorner, &vEffectCenter, pEffectSphere->fRadius))
		{
			((CEffect*)_pEffect)->AddCnt();
			((CMonster*)_pMonster)->Damage((CEffect*)_pEffect);
			pEffectSphere->ExceptVec.push_back(_pMonster);
			return;
		}
	}
}

void CCollisionMgr::PlayerToNPC(CObject* _pPlayer, CObject* _pNPC)
{
	// Center
	D3DXVECTOR3 vPlayerCenter;
	D3DXVECTOR3 vNPCCenter;

	// Sphere
	Sphere* pPlayerSphere;
	Sphere* pNPCSphere;

	// CollisionCom
	CCollisionCom* pPlayerCollisionCom = (CCollisionCom*)_pPlayer->GetComponent(COM_TYPE_COLLISION);
	CCollisionCom* pNPCCollisionCom = (CCollisionCom*)_pNPC->GetComponent(COM_TYPE_COLLISION);

	// CheckSphere
	pPlayerSphere = pPlayerCollisionCom->m_pCheckSphere;
	pNPCSphere = pNPCCollisionCom->m_pCheckSphere;

	D3DXVec3TransformCoord(&vPlayerCenter, &pPlayerSphere->vCenter, pPlayerSphere->pMatrix);
	D3DXVec3TransformCoord(&vNPCCenter, &pNPCSphere->vCenter, pNPCSphere->pMatrix);

	vPlayerCenter += pPlayerCollisionCom->m_vPushed;
	vNPCCenter += pNPCCollisionCom->m_vPushed;

	if(CircleToCircle(&D3DXVECTOR2(vPlayerCenter.x, vPlayerCenter.z), pPlayerSphere->fRadius, &D3DXVECTOR2(vNPCCenter.x, vNPCCenter.z), pNPCSphere->fRadius) == false)
		return;

	// CollisionShpere
	pPlayerSphere = pPlayerCollisionCom->m_pCollisionSphere;
	pNPCSphere = pNPCCollisionCom->m_pCollisionSphere;

	D3DXVec3TransformCoord(&vPlayerCenter, &pPlayerSphere->vCenter, pPlayerSphere->pMatrix);
	D3DXVec3TransformCoord(&vNPCCenter, &pNPCSphere->vCenter, pNPCSphere->pMatrix);

	vPlayerCenter += pPlayerCollisionCom->m_vPushed;
	vNPCCenter += pNPCCollisionCom->m_vPushed;

	if(CircleToCircle(&D3DXVECTOR2(vPlayerCenter.x, vPlayerCenter.z), pPlayerSphere->fRadius, &D3DXVECTOR2(vNPCCenter.x, vNPCCenter.z), pNPCSphere->fRadius))
	{
		// PathFindCom
		CPathFindCom* pPlayerPathFindCom = (CPathFindCom*)_pPlayer->GetComponent(COM_TYPE_PATH_FIND);

		D3DXVECTOR3 vNPCToPlayer = vPlayerCenter - vNPCCenter;
		if(!Equals(vNPCToPlayer.x, 0.0f, MIN_EPSILON) || !Equals(vNPCToPlayer.z, 0.0f, MIN_EPSILON))
		{
			// NPCToPlayer
			vNPCToPlayer.y = 0.0f;
			D3DXVec3Normalize(&vNPCToPlayer, &vNPCToPlayer);

			// TransformCom
			CTransformCom* pTransformCom = (CTransformCom*)_pPlayer->GetComponent(COM_TYPE_TRANSFORM);

			// NextPos
			D3DXVECTOR3 vNextPos = vNPCCenter + vNPCToPlayer * (pPlayerSphere->fRadius + pNPCSphere->fRadius + MIN_EPSILON);

			// Solution
			CNaviCell* pNextCell;
			CPathFindMgr::GetInstance()->Solution(&pTransformCom->m_vPos, pPlayerPathFindCom->m_pCell, &vNextPos, &pNextCell);

			// Pushed
			pPlayerCollisionCom->m_vPushed += vNextPos - pTransformCom->m_vPos;

			// Pos
			pTransformCom->m_vPos = vNextPos;
			pPlayerPathFindCom->m_pCell = pNextCell;
		}
	}
}

void CCollisionMgr::PlayerToProb(CObject* _pPlayer, CObject* _pProb)
{
	// CollisionCom
	CCollisionCom* pPlayerCollisionCom = (CCollisionCom*)_pPlayer->GetComponent(COM_TYPE_COLLISION);
	CCollisionCom* pProbCollisionCom = (CCollisionCom*)_pProb->GetComponent(COM_TYPE_COLLISION);

	// CheckShpere
	Sphere* pPlayerSphere = pPlayerCollisionCom->m_pCheckSphere;
	Sphere* pProbSphere = pProbCollisionCom->m_pCheckSphere;

	// Center
	D3DXVECTOR3 vPlayerCenter;
	D3DXVECTOR3 vProbCenter;

	D3DXVec3TransformCoord(&vPlayerCenter, &pPlayerSphere->vCenter, pPlayerSphere->pMatrix);
	D3DXVec3TransformCoord(&vProbCenter, &pProbSphere->vCenter, pProbSphere->pMatrix);

	vPlayerCenter += pPlayerCollisionCom->m_vPushed;
	vProbCenter += pProbCollisionCom->m_vPushed;

	if(CircleToCircle(&D3DXVECTOR2(vPlayerCenter.x, vPlayerCenter.z), pPlayerSphere->fRadius, &D3DXVECTOR2(vProbCenter.x, vProbCenter.z), pProbSphere->fRadius) == false)
		return;

	// ProbCollision
	pPlayerSphere = pPlayerCollisionCom->m_pCollisionSphere;
	Collision* pProbCollision = pProbCollisionCom->m_pCollisionBox;

	// PlayerCenter
	D3DXVec3TransformCoord(&vPlayerCenter, &pPlayerSphere->vCenter, pPlayerSphere->pMatrix);
	vPlayerCenter += pPlayerCollisionCom->m_vPushed;

	// ProbCenter
	D3DXVec3TransformCoord(&vProbCenter, &pProbCollision->vCenter, pProbCollision->pMatrix);
	vProbCenter += pProbCollisionCom->m_vPushed;

	// v
	D3DXVECTOR3 v[4];
	v[0] = vProbCenter - pProbCollision->vAxisX * pProbCollision->fWidth / 2.0f - pProbCollision->vAxisY * (pProbCollision->fHeight / 2.0f + pPlayerSphere->fRadius) - pProbCollision->vAxisZ * pProbCollision->fDepth / 2.0f;
	v[1] = vProbCenter - pProbCollision->vAxisX * pProbCollision->fWidth / 2.0f - pProbCollision->vAxisY * (pProbCollision->fHeight / 2.0f + pPlayerSphere->fRadius) + pProbCollision->vAxisZ * pProbCollision->fDepth / 2.0f;
	v[2] = vProbCenter + pProbCollision->vAxisX * pProbCollision->fWidth / 2.0f - pProbCollision->vAxisY * (pProbCollision->fHeight / 2.0f + pPlayerSphere->fRadius) + pProbCollision->vAxisZ * pProbCollision->fDepth / 2.0f;
	v[3] = vProbCenter + pProbCollision->vAxisX * pProbCollision->fWidth / 2.0f - pProbCollision->vAxisY * (pProbCollision->fHeight / 2.0f + pPlayerSphere->fRadius) - pProbCollision->vAxisZ * pProbCollision->fDepth / 2.0f;

	// line
	CNaviLine line[4];
	line[0].Setup(&v[0], &v[1]);
	line[1].Setup(&v[1], &v[2]);
	line[2].Setup(&v[2], &v[3]);
	line[3].Setup(&v[3], &v[0]);

	// PlayerTransformCom
	CTransformCom* pPlayerTransformCom = (CTransformCom*)_pPlayer->GetComponent(COM_TYPE_TRANSFORM);

	// PlayerPathFindCom
	CPathFindCom* pPlayerPathFindCom = (CPathFindCom*)_pPlayer->GetComponent(COM_TYPE_PATH_FIND);

	// CurPos
	D3DXVECTOR3 vCurPos = vPlayerCenter;

	// PrePos
	D3DXVECTOR3 vPrePos = vCurPos - pPlayerPathFindCom->m_vDir;

	// Move
	CNaviLine MoveLine;
	MoveLine.Setup(&vPrePos, &vCurPos);

	// IntersectPoint
	D3DXVECTOR3 vIntersectPoint;

	for(int i = 0; i < 4; ++i)
	{
		if(line[i].Classify(&MoveLine, &vIntersectPoint) == LINE_CLASS_SEGMENT)
		{
			// NextPos
			D3DXVECTOR3 vNextPos = vIntersectPoint - line[i].m_vNormal + line[i].m_vDir;

			// Solution
			CNaviCell* pNextCell;
			CPathFindMgr::GetInstance()->Solution(&vCurPos, pPlayerPathFindCom->m_pCell, &vNextPos, &pNextCell);

			// DstPos
			pPlayerCollisionCom->m_vPushed += vNextPos - vCurPos;
			pPlayerTransformCom->m_vPos = vNextPos;
			pPlayerPathFindCom->m_pCell = pNextCell;

			break;
		}
	}
}