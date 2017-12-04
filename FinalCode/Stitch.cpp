#include "StdAfx.h"
#include "Stitch.h"

CStitch::CStitch(TCHAR*	_tszObjKey, OBJ_TYPE _eObjType, int _iLevel)
: CMonster(_tszObjKey, _eObjType, _iLevel)
{
	// Info
	_tcscpy_s(m_info.tszName, MIN_STR, _T("±â±«»ìµ¢ÀÌ"));

	// Stat
	m_stat.iLife = m_stat.iMaxLife = _iLevel * 16000;
	m_stat.iStrength = _iLevel * 50;

	// CollisionCom
	m_pCollisionCom = new CCollisionCom(COLL_TYPE_MONSTER, new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 60.0f), new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f));
	m_pCollisionCom->m_CollisionVec.push_back(new Collision(COLLISION_DAMAGE, &m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 50.0f, 0.0f), 50.0f, 80.0f, 50.0f));
	AddComponent(m_pCollisionCom);

	// PathFindCom
	CPathFindCom* pPathFindCom = new CPathFindCom(PATH_TYPE_MONSTER, 80.0f);
	AddComponent(pPathFindCom);

	// BufferCom
	CBufferCom* pBufferCom = new CBufferCom;
	pBufferCom->AddBuffer(_T("Stitch"));
	AddComponent(pBufferCom);

	// RightHandBone
	CDynamicMesh*	pDynamicMesh = (CDynamicMesh*)pBufferCom->m_BufferVec[0];
	m_RightHandBone.pFrame = (MeshFrame*)D3DXFrameFind(pDynamicMesh->m_pRootFrame, "right_wrist");

	// RightElbowBone
	m_RightElbowBone.pFrame = (MeshFrame*)D3DXFrameFind(pDynamicMesh->m_pRootFrame, "right_elbow");

	// Spike
	m_SpikeABone.pFrame = (MeshFrame*)D3DXFrameFind(pDynamicMesh->m_pRootFrame, "Spike_A");
	m_SpikeBBone.pFrame = (MeshFrame*)D3DXFrameFind(pDynamicMesh->m_pRootFrame, "Spike_B");
	m_SpikeCBone.pFrame = (MeshFrame*)D3DXFrameFind(pDynamicMesh->m_pRootFrame, "Spike_C");
	m_SpikeDBone.pFrame = (MeshFrame*)D3DXFrameFind(pDynamicMesh->m_pRootFrame, "Spike_D");
	m_SpikeEBone.pFrame = (MeshFrame*)D3DXFrameFind(pDynamicMesh->m_pRootFrame, "Spike_E");
	m_SpikeFBone.pFrame = (MeshFrame*)D3DXFrameFind(pDynamicMesh->m_pRootFrame, "Spike_F");
	m_SpikeGBone.pFrame = (MeshFrame*)D3DXFrameFind(pDynamicMesh->m_pRootFrame, "Spike_G");
	m_SpikeHBone.pFrame = (MeshFrame*)D3DXFrameFind(pDynamicMesh->m_pRootFrame, "Spike_H");
	m_SpikeIBone.pFrame = (MeshFrame*)D3DXFrameFind(pDynamicMesh->m_pRootFrame, "Spike_I");
	m_SpikeJBone.pFrame = (MeshFrame*)D3DXFrameFind(pDynamicMesh->m_pRootFrame, "Spike_J");
	m_SpikeKBone.pFrame = (MeshFrame*)D3DXFrameFind(pDynamicMesh->m_pRootFrame, "Spike_K");
}

CStitch::~CStitch()
{
	Release();
}

void CStitch::Initialize()
{
	CMonster::Initialize();
}

int CStitch::Update()
{
	CMonster::Update();

	m_RightHandBone.mWorld = m_RightHandBone.pFrame->mCombinedMatrix * m_pTransformCom->m_mWorld;
	m_RightElbowBone.mWorld = m_RightElbowBone.pFrame->mCombinedMatrix * m_pTransformCom->m_mWorld;

	m_SpikeABone.mWorld = m_SpikeABone.pFrame->mCombinedMatrix * m_pTransformCom->m_mWorld;
	m_SpikeBBone.mWorld = m_SpikeBBone.pFrame->mCombinedMatrix * m_pTransformCom->m_mWorld;
	m_SpikeCBone.mWorld = m_SpikeCBone.pFrame->mCombinedMatrix * m_pTransformCom->m_mWorld;
	m_SpikeDBone.mWorld = m_SpikeDBone.pFrame->mCombinedMatrix * m_pTransformCom->m_mWorld;
	m_SpikeEBone.mWorld = m_SpikeEBone.pFrame->mCombinedMatrix * m_pTransformCom->m_mWorld;
	m_SpikeFBone.mWorld = m_SpikeFBone.pFrame->mCombinedMatrix * m_pTransformCom->m_mWorld;
	m_SpikeGBone.mWorld = m_SpikeGBone.pFrame->mCombinedMatrix * m_pTransformCom->m_mWorld;
	m_SpikeHBone.mWorld = m_SpikeHBone.pFrame->mCombinedMatrix * m_pTransformCom->m_mWorld;
	m_SpikeIBone.mWorld = m_SpikeIBone.pFrame->mCombinedMatrix * m_pTransformCom->m_mWorld;
	m_SpikeJBone.mWorld = m_SpikeJBone.pFrame->mCombinedMatrix * m_pTransformCom->m_mWorld;
	m_SpikeKBone.mWorld = m_SpikeKBone.pFrame->mCombinedMatrix * m_pTransformCom->m_mWorld;

	return 0;
}

void CStitch::Render()
{
	CMonster::Render();
}

void CStitch::Release()
{
}

void CStitch::CreateAttack()
{
	if(m_pCollisionCom == NULL)
		return;

	switch (m_pState->GetStateType())
	{
	case STATE_TYPE_STITCH_ATTACK :
		m_pCollisionCom->m_CollisionVec.push_back(new Collision(COLLISION_ATTACK, &m_RightHandBone.mWorld, &D3DXVECTOR3(0.f, 0.f, 0.f), 30.f, 30.f, 30.f));
		break;
	case STATE_TYPE_STITCH_ATTACK2 :
		m_pCollisionCom->m_CollisionVec.push_back(new Collision(COLLISION_ATTACK, &m_RightElbowBone.mWorld, &D3DXVECTOR3(0.f, 0.f, 0.f), 30.f, 30.f, 30.f));
		break;
	case STATE_TYPE_STITCH_ATTACK3 :
		m_pCollisionCom->m_CollisionVec.push_back(new Collision(COLLISION_ATTACK, &m_RightHandBone.mWorld, &D3DXVECTOR3(0.f, 60.f, 0.f), 30.f, 30.f, 30.f));
		break;
	case STATE_TYPE_STITCH_DEATH :
		break;
	case STATE_TYPE_STITCH_HIT :
		break;
	case STATE_TYPE_STITCH_IDLE :
		break;
	case STATE_TYPE_STITCH_WALK :
		break;
	case STATE_TYPE_STITCH_RUN :
		break;
	}

	// CreateAttack
	CMonster::CreateAttack();
}

void CStitch::Damage(CPlayer* _pPlayer)
{
	// PreLife
	int iPreLife = m_stat.iLife;

	// Damage
	CMonster::Damage(_pPlayer);

	// CurLife
	int iCurLife = m_stat.iLife;

	// Death
	if(m_stat.iLife <= 0 && m_pState->GetStateType() != STATE_TYPE_STITCH_DEATH)
	{
		SetState(new CStitch_Death);
		return;
	}

	// Hit
	if(iCurLife - iPreLife > m_stat.iMaxLife * 0.3f)
	{
		SetState(new CStitch_Hit);
		return;
	}
	else
	{
		if(m_pState != NULL && m_pState->GetStateType() != STATE_TYPE_STITCH_RUN)
		{
			SetState(new CStitch_Run(1));
			return;
		}
	}
}

void CStitch::Damage(CEffect* _pEffect)
{
	// PreLife
	int iPreLife = m_stat.iLife;

	// Damage
	CMonster::Damage(_pEffect);

	// CurLife
	int iCurLife = m_stat.iLife;

	// Death
	if(m_stat.iLife <= 0 && m_pState->GetStateType() != STATE_TYPE_STITCH_DEATH)
	{
		SetState(new CStitch_Death);
		return;
	}

	// Hit
	if(iCurLife - iPreLife > m_stat.iMaxLife * 0.3f)
	{
		SetState(new CStitch_Hit);
		return;
	}
	else
	{
		if(m_pState != NULL && m_pState->GetStateType() != STATE_TYPE_STITCH_RUN)
		{
			SetState(new CStitch_Run(1));
			return;
		}
	}
}