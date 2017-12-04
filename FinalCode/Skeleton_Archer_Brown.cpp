#include "StdAfx.h"
#include "Skeleton_Archer_Brown.h"

CSkeleton_Archer_Brown::CSkeleton_Archer_Brown(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, int _iLevel)
: CMonster(_tszObjKey, _eObjType, _iLevel)
{
	// Info
	_tcscpy_s(m_info.tszName, MIN_STR, _T("¼ö°¨µÈ ¹Ð·Æ²Û"));

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
	pBufferCom->AddBuffer(_T("Skeleton_Archer_Brown"));
	AddComponent(pBufferCom);

	// WeaponBone
	CDynamicMesh*	pDynamicMesh = (CDynamicMesh*)pBufferCom->m_BufferVec[0];
	m_WeaponBone.pFrame = (MeshFrame*)D3DXFrameFind(pDynamicMesh->m_pRootFrame, "left_weapon");
}

CSkeleton_Archer_Brown::~CSkeleton_Archer_Brown()
{
	Release();
}

void CSkeleton_Archer_Brown::Initialize()
{
	CMonster::Initialize();
}

int CSkeleton_Archer_Brown::Update()
{
	CMonster::Update();

	m_WeaponBone.mWorld = m_WeaponBone.pFrame->mCombinedMatrix * m_pTransformCom->m_mWorld;

	return 0;
}

void CSkeleton_Archer_Brown::Render()
{
	CMonster::Render();
}

void CSkeleton_Archer_Brown::Release()
{
}

void CSkeleton_Archer_Brown::CreateAttack()
{
	if(m_pCollisionCom == NULL)
		return;

	switch(m_pState->GetStateType())
	{
	case STATE_TYPE_SKELETON_ARCHER_BROWN_ATTACK :
		break;
	case STATE_TYPE_SKELETON_ARCHER_BROWN_DEATH :
		break;
	case STATE_TYPE_SKELETON_ARCHER_BROWN_HIT :
		break;
	case STATE_TYPE_SKELETON_ARCHER_BROWN_IDLE :
		break;
	case STATE_TYPE_SKELETON_ARCHER_BROWN_RUN :
		break;
	case STATE_TYPE_SKELETON_ARCHER_BROWN_SPAWN : 
		break;
	case STATE_TYPE_SKELETON_ARCHER_BROWN_WALK :
		break;
	}

	// CreateAttack
	CMonster::CreateAttack();
}

void CSkeleton_Archer_Brown::Damage(CPlayer* _pPlayer)
{
	// PreLife
	int iPreLife = m_stat.iLife;

	// Damage
	CMonster::Damage(_pPlayer);

	// CurLife
	int iCurLife = m_stat.iLife;

	// Death
	if(m_stat.iLife <= 0 && m_pState->GetStateType() != STATE_TYPE_SKELETON_ARCHER_BROWN_DEATH)
	{
		SetState(new CSkeleton_Archer_Brown_Death);
		return;
	}

	// Hit
	if(iCurLife - iPreLife > m_stat.iMaxLife * 0.3f)
	{
		SetState(new CSkeleton_Archer_Brown_Hit);
		return;
	}
	else 
	{
		if(m_pState != NULL && m_pState->GetStateType() != STATE_TYPE_SKELETON_ARCHER_BROWN_RUN)
		{
			SetState(new CSkeleton_Archer_Brown_Run(2));
			return;
		}
	}
}

void CSkeleton_Archer_Brown::Damage(CEffect* _pEffect)
{
	// PreLife
	int iPreLife = m_stat.iLife;

	// Damage
	CMonster::Damage(_pEffect);

	// CurLife
	int iCurLife = m_stat.iLife;

	// Death
	if(m_stat.iLife <= 0 && m_pState->GetStateType() != STATE_TYPE_SKELETON_ARCHER_BROWN_DEATH)
	{
		SetState(new CSkeleton_Archer_Brown_Death);
		return;
	}

	// Hit
	if(iCurLife - iPreLife > m_stat.iMaxLife * 0.3f)
	{
		SetState(new CSkeleton_Archer_Brown_Hit);
		return;
	}
	else 
	{
		if(m_pState != NULL && m_pState->GetStateType() != STATE_TYPE_SKELETON_ARCHER_BROWN_RUN)
		{
			SetState(new CSkeleton_Archer_Brown_Run(2));
			return;
		}
	}
}