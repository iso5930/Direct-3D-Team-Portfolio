#include "StdAfx.h"
#include "Skeleton_Summoner_Brown_Magic.h"

CSkeleton_Summoner_Brown_Magic::CSkeleton_Summoner_Brown_Magic(int _iMode)
{
	// StateType
	m_eStateType = STATE_TYPE_SKELETON_SUMMONER_BROWN_MAGIC;

	// Mode
	m_iMode = _iMode;

	// Effect
	m_pArcaneBall = NULL;
	m_bEffect = false;
}

CSkeleton_Summoner_Brown_Magic::~CSkeleton_Summoner_Brown_Magic(void)
{
}

void CSkeleton_Summoner_Brown_Magic::Initialize()
{
	CMonsterState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(2);

	CSoundMgr::GetInstance()->PlaySoundForMonster(_T("Skeleton_Summoner_Magic.ogg"));
}

CMonsterState* CSkeleton_Summoner_Brown_Magic::Action()
{
	if(!m_bEffect && m_pAnimController->GetTrackPos() > 2.343f)
	{
		D3DXVECTOR3 vLook = D3DXVECTOR3(0.f, 0.f, 0.f);
		memcpy(&vLook, &m_pTransformCom->m_mWorld.m[2][0], sizeof(D3DXVECTOR3));
		vLook.y = 0.f;
		D3DXVec3Normalize(&vLook, &vLook);

		m_pArcaneBall = new CSkeletonSummoner_ArcaneBall(NULL, OBJ_TYPE_DYNAMIC, m_pOwner, &(-vLook * 500.f));
		m_pOwner->GetLayer()->AddObject(m_pArcaneBall, LAYER_TYPE_EFFECT);

		CTransformCom* pTransformCom = (CTransformCom*)m_pArcaneBall->GetComponent(COM_TYPE_TRANSFORM);
		D3DXVec3TransformCoord(&pTransformCom->m_vPos, &pTransformCom->m_vPos, &((CSkeleton_Summoner_Brown*)m_pOwner)->m_LeftHandBone.mWorld);
		pTransformCom->m_vAngle = m_pTransformCom->m_vAngle;

		m_pArcaneBall->Initialize();
		m_bEffect = true;
	}

	switch(m_iMode)
	{
	case 0:
		return Mode0();
	case 1:
		return Mode1();
	}

	return NULL;
}

CMonsterState* CSkeleton_Summoner_Brown_Magic::Mode0()
{
	// Player
	CObject* pPlayer = NULL;
	m_pOwner->GetLayer()->FindObject(pPlayer, _T("Player"), LAYER_TYPE_PLAYER);
	if(pPlayer == NULL)
		return NULL;

	// PlayerTransformCom
	CTransformCom* pPlayerTransformCom = (CTransformCom*)pPlayer->GetComponent(COM_TYPE_TRANSFORM);

	if(D3DXVec3Length(&(pPlayerTransformCom->m_vPos - m_pTransformCom->m_vPos)) < 300.0f
		&& D3DXVec3Length(&(pPlayerTransformCom->m_vPos - m_pTransformCom->m_vPos)) > 200.0f)
	{

		// Dir
		D3DXVECTOR3 vDir = pPlayerTransformCom->m_vPos - m_pTransformCom->m_vPos;

		if(m_pAnimController->GetTrackPos() < 0.45)
		{
			if(!Equals(vDir.x, 0.0f, MIN_EPSILON) || !Equals(vDir.z, 0.0f, MIN_EPSILON))
			{
				// Normalize
				vDir.y = 0.0f;
				D3DXVec3Normalize(&vDir, &vDir);

				// DotX
				float fDotX = D3DXVec3Dot(&-m_pTransformCom->m_vAxisX, &vDir);
				fDotX = RevisionDot(fDotX);

				// DotZ
				float fDotZ = D3DXVec3Dot(&-m_pTransformCom->m_vAxisZ, &vDir);
				fDotZ = RevisionDot(fDotZ);

				if(fDotX > 0.0f)
					m_pTransformCom->m_vAngle.y += acosf(fDotZ);
				else
					m_pTransformCom->m_vAngle.y -= acosf(fDotZ);
			}
		}
		if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
			return new CSkeleton_Summoner_Brown_Idle(1);

	}

	else if(D3DXVec3Length(&(pPlayerTransformCom->m_vPos - m_pTransformCom->m_vPos)) <= 200.0f)
	{
		if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
		{
			return new CSkeleton_Summoner_Brown_Walk(2);
		}
	}
	else if(D3DXVec3Length(&(pPlayerTransformCom->m_vPos - m_pTransformCom->m_vPos)) > 300.0f
		&& m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
		return new CSkeleton_Summoner_Brown_Idle(0);

	return NULL;
}

CMonsterState* CSkeleton_Summoner_Brown_Magic::Mode1()
{
	// Player
	CObject* pPlayer = NULL;
	m_pOwner->GetLayer()->FindObject(pPlayer, _T("Player"), LAYER_TYPE_PLAYER);
	if(pPlayer == NULL)
		return NULL;

	// PlayerTransformCom
	CTransformCom* pPlayerTransformCom = (CTransformCom*)pPlayer->GetComponent(COM_TYPE_TRANSFORM);

	if(D3DXVec3Length(&(pPlayerTransformCom->m_vPos - m_pTransformCom->m_vPos)) < 300.0f)
	{

		// Dir
		D3DXVECTOR3 vDir = pPlayerTransformCom->m_vPos - m_pTransformCom->m_vPos;

		if(m_pAnimController->GetTrackPos() < 0.45)
		{
			if(!Equals(vDir.x, 0.0f, MIN_EPSILON) || !Equals(vDir.z, 0.0f, MIN_EPSILON))
			{
				// Normalize
				vDir.y = 0.0f;
				D3DXVec3Normalize(&vDir, &vDir);

				// DotX
				float fDotX = D3DXVec3Dot(&-m_pTransformCom->m_vAxisX, &vDir);
				fDotX = RevisionDot(fDotX);

				// DotZ
				float fDotZ = D3DXVec3Dot(&-m_pTransformCom->m_vAxisZ, &vDir);
				fDotZ = RevisionDot(fDotZ);

				if(fDotX > 0.0f)
					m_pTransformCom->m_vAngle.y += acosf(fDotZ);
				else
					m_pTransformCom->m_vAngle.y -= acosf(fDotZ);
			}
		}
		if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
			return new CSkeleton_Summoner_Brown_Magic(1);

	}

	else if(D3DXVec3Length(&(pPlayerTransformCom->m_vPos - m_pTransformCom->m_vPos)) < 150.0f)
	{
		if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
		{
			return new CSkeleton_Summoner_Brown_Walk(2);
		}
	}
	return NULL;
}
