#include "StdAfx.h"
#include "Skeleton_Summoner_Blue.h"

CSkeleton_Summoner_Blue::CSkeleton_Summoner_Blue(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, int _iLevel)
: CMonster(_tszObjKey, _eObjType, _iLevel)
{
	// Info
	_tcscpy_s(m_info.tszName, MIN_STR, _T("고문당한 소환사"));

	// Stat
	m_stat.iLife = m_stat.iMaxLife = _iLevel * 8000;
	m_stat.iStrength = _iLevel * 40;

	// CollisionCom
	m_pCollisionCom = new CCollisionCom(COLL_TYPE_MONSTER, new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 60.0f), new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 30.0f));
	m_pCollisionCom->m_CollisionVec.push_back(new Collision(COLLISION_DAMAGE, &m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 50.0f, 0.0f), 20.0f, 50.0f, 20.0f));
	AddComponent(m_pCollisionCom);

	// PathFindCom
	CPathFindCom* pPathFindCom = new CPathFindCom(PATH_TYPE_MONSTER, 80.0f);
	AddComponent(pPathFindCom);

	// BufferCom
	CBufferCom* pBufferCom = new CBufferCom;
	pBufferCom->AddBuffer(_T("Skeleton_Summoner_Blue"));
	AddComponent(pBufferCom);

	// WeaponBone
	CDynamicMesh*	pDynamicMesh = (CDynamicMesh*)pBufferCom->m_BufferVec[0];
	m_LeftHandBone.pFrame = (MeshFrame*)D3DXFrameFind(pDynamicMesh->m_pRootFrame, "left_index1");
	m_RightHandBone.pFrame = (MeshFrame*)D3DXFrameFind(pDynamicMesh->m_pRootFrame, "right_index1");
	m_CenterBone.pFrame = (MeshFrame*)D3DXFrameFind(pDynamicMesh->m_pRootFrame, "Spine2");
}

CSkeleton_Summoner_Blue::~CSkeleton_Summoner_Blue()
{
	Release();
}

void CSkeleton_Summoner_Blue::Initialize()
{
	CMonster::Initialize();
}

int CSkeleton_Summoner_Blue::Update()
{
	CMonster::Update();

	m_LeftHandBone.mWorld = m_LeftHandBone.pFrame->mCombinedMatrix * m_pTransformCom->m_mWorld;
	m_RightHandBone.mWorld = m_RightHandBone.pFrame->mCombinedMatrix * m_pTransformCom->m_mWorld;
	m_CenterBone.mWorld = m_CenterBone.pFrame->mCombinedMatrix * m_pTransformCom->m_mWorld;

	return 0;
}

void CSkeleton_Summoner_Blue::Render()
{
	CMonster::Render();
}

void CSkeleton_Summoner_Blue::Release()
{
}

void CSkeleton_Summoner_Blue::CreateAttack()
{
	if(m_pCollisionCom == NULL)
		return;

	switch(m_pState->GetStateType())
	{
	case STATE_TYPE_SKELETON_SUMMONER_BLUE_DEATH :
		break;
	case STATE_TYPE_SKELETON_SUMMONER_BLUE_HIT :
		break;
	case STATE_TYPE_SKELETON_SUMMONER_BLUE_IDLE :
		break;
	case STATE_TYPE_SKELETON_SUMMONER_BLUE_MAGIC :
		break;
	case STATE_TYPE_SKELETON_SUMMONER_BLUE_SUMMON :
		break;
	case STATE_TYPE_SKELETON_SUMMONER_BLUE_WALK : 
		break;
	}

	// CreateAttack
	CMonster::CreateAttack();
}

void CSkeleton_Summoner_Blue::Damage(CPlayer* _pPlayer)
{
	// PreLife
	int iPreLife = m_stat.iLife;

	// Damage
	CMonster::Damage(_pPlayer);

	// CurLife
	int iCurLife = m_stat.iLife;

	// Death
	if(m_stat.iLife <= 0 && m_pState->GetStateType() != STATE_TYPE_SKELETON_SUMMONER_BLUE_DEATH)
	{
		SetState(new CSkeleton_Summoner_Blue_Death);
		return;
	}

	// Hit
	if(iCurLife - iPreLife > m_stat.iMaxLife * 0.3f)
	{
		SetState(new CSkeleton_Summoner_Blue_Hit);
		return;
	}
	else
	{
		if(m_pState != NULL && m_pState->GetStateType() != STATE_TYPE_SKELETON_SUMMONER_BLUE_WALK)
		{
			SetState(new CSkeleton_Summoner_Blue_Walk(3));
			return;
		}
	}
}

void CSkeleton_Summoner_Blue::Damage(CEffect* _pEffect)
{
	// PreLife
	int iPreLife = m_stat.iLife;

	// Damage
	CMonster::Damage(_pEffect);

	// CurLife
	int iCurLife = m_stat.iLife;

	// Death
	if(m_stat.iLife <= 0 && m_pState->GetStateType() != STATE_TYPE_SKELETON_SUMMONER_BLUE_DEATH)
	{
		SetState(new CSkeleton_Summoner_Blue_Death);
		return;
	}

	// Hit
	if(iCurLife - iPreLife > m_stat.iMaxLife * 0.3f)
	{
		SetState(new CSkeleton_Summoner_Blue_Hit);
		return;
	}
	else
	{
		if(m_pState != NULL && m_pState->GetStateType() != STATE_TYPE_SKELETON_SUMMONER_BLUE_WALK)
		{
			SetState(new CSkeleton_Summoner_Blue_Walk(3));
			return;
		}
	}
}