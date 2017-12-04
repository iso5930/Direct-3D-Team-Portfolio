#include "StdAfx.h"
#include "Skeleton_Archer_Mint.h"

CSkeleton_Archer_Mint::CSkeleton_Archer_Mint(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, int _iLevel)
: CMonster(_tszObjKey, _eObjType, _iLevel)
{
	// Info
	_tcscpy_s(m_info.tszName, MIN_STR, _T("ÇØ°ñ ±Ã¼ö"));

	// Stat
	m_stat.iLife = m_stat.iMaxLife = _iLevel * 1000;
	m_stat.iStrength = _iLevel * 10;

	// CollisionCom
	m_pCollisionCom = new CCollisionCom(COLL_TYPE_MONSTER, new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 60.0f), new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 30.0f));
	m_pCollisionCom->m_CollisionVec.push_back(new Collision(COLLISION_DAMAGE, &m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 50.0f, 0.0f), 20.0f, 50.0f, 20.0f));
	AddComponent(m_pCollisionCom);

	// PathFindCom
	CPathFindCom* pPathFindCom = new CPathFindCom(PATH_TYPE_MONSTER, 80.0f);
	AddComponent(pPathFindCom);

	// BufferCom
	CBufferCom* pBufferCom = new CBufferCom;
	pBufferCom->AddBuffer(_T("Skeleton_Archer_Mint"));
	AddComponent(pBufferCom);

	// WeaponBone
	CDynamicMesh*	pDynamicMesh = (CDynamicMesh*)pBufferCom->m_BufferVec[0];
	m_WeaponBone.pFrame = (MeshFrame*)D3DXFrameFind(pDynamicMesh->m_pRootFrame, "left_weapon");
}

CSkeleton_Archer_Mint::~CSkeleton_Archer_Mint()
{
	Release();
}

void CSkeleton_Archer_Mint::Initialize()
{
	CMonster::Initialize();
}

int CSkeleton_Archer_Mint::Update()
{
	CMonster::Update();

	m_WeaponBone.mWorld = m_WeaponBone.pFrame->mCombinedMatrix * m_pTransformCom->m_mWorld;

	return 0;
}

void CSkeleton_Archer_Mint::Render()
{
	CMonster::Render();
}

void CSkeleton_Archer_Mint::Release()
{
}

void CSkeleton_Archer_Mint::CreateAttack()
{
	if(m_pCollisionCom == NULL)
		return;

	switch(m_pState->GetStateType())
	{
	case STATE_TYPE_SKELETON_ARCHER_MINT_ATTACK :
		break;
	case STATE_TYPE_SKELETON_ARCHER_MINT_DEATH :
		break;
	case STATE_TYPE_SKELETON_ARCHER_MINT_HIT :
		break;
	case STATE_TYPE_SKELETON_ARCHER_MINT_IDLE :
		break;
	case STATE_TYPE_SKELETON_ARCHER_MINT_RUN :
		break;
	case STATE_TYPE_SKELETON_ARCHER_MINT_SPAWN : 
		break;
	case STATE_TYPE_SKELETON_ARCHER_MINT_WALK :
		break;
	}

	// CreateAttack
	CMonster::CreateAttack();
}

void CSkeleton_Archer_Mint::Damage(CPlayer* _pPlayer)
{
	// PreLife
	int iPreLife = m_stat.iLife;

	// Damage
	CMonster::Damage(_pPlayer);

	// CurLife
	int iCurLife = m_stat.iLife;

	// Death
	if(m_stat.iLife <= 0 && m_pState->GetStateType() != STATE_TYPE_SKELETON_ARCHER_MINT_DEATH)
	{
		SetState(new CSkeleton_Archer_Mint_Death);
		return;
	}

	// Hit
	if(iCurLife - iPreLife > m_stat.iMaxLife * 0.3f)
	{
		SetState(new CSkeleton_Archer_Mint_Hit);
		return;
	}
	else 
	{
		if(m_pState != NULL && m_pState->GetStateType() != STATE_TYPE_SKELETON_ARCHER_MINT_RUN)
		{
			SetState(new CSkeleton_Archer_Mint_Run(2));
			return;
		}
	}
}

void CSkeleton_Archer_Mint::Damage(CEffect* _pEffect)
{
	// PreLife
	int iPreLife = m_stat.iLife;

	// Damage
	CMonster::Damage(_pEffect);

	// CurLife
	int iCurLife = m_stat.iLife;

	// Death
	if(m_stat.iLife <= 0 && m_pState->GetStateType() != STATE_TYPE_SKELETON_ARCHER_MINT_DEATH)
	{
		SetState(new CSkeleton_Archer_Mint_Death);
		return;
	}

	// Hit
	if(iCurLife - iPreLife > m_stat.iMaxLife * 0.3f)
	{
		SetState(new CSkeleton_Archer_Mint_Hit);
		return;
	}
	else 
	{
		if(m_pState != NULL && m_pState->GetStateType() != STATE_TYPE_SKELETON_ARCHER_MINT_RUN)
		{
			SetState(new CSkeleton_Archer_Mint_Run(2));
			return;
		}
	}
}