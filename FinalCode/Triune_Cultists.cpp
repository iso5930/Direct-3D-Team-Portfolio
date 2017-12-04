#include "StdAfx.h"
#include "Triune_Cultists.h"

CTriune_Cultists::CTriune_Cultists(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, int _iLevel)
: CMonster(_tszObjKey, _eObjType, _iLevel)
{
	// Info
	_tcscpy_s(m_info.tszName, MIN_STR, _T("¾îµÒÀÇ ±¤½Åµµ"));

	// Stat
	m_stat.iLife = m_stat.iMaxLife = _iLevel * 4000;
	m_stat.iStrength = _iLevel * 30;

	// CollisionCom
	m_pCollisionCom = new CCollisionCom(COLL_TYPE_MONSTER, new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 60.0f), new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 30.0f));
	m_pCollisionCom->m_CollisionVec.push_back(new Collision(COLLISION_DAMAGE, &m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 50.0f, 0.0f), 30.0f, 60.0f, 30.0f));
	AddComponent(m_pCollisionCom);

	// PathFindCom
	CPathFindCom* pPathFindCom = new CPathFindCom(PATH_TYPE_MONSTER, 120.0f);
	AddComponent(pPathFindCom);

	// BufferCom
	CBufferCom* pBufferCom = new CBufferCom;
	pBufferCom->AddBuffer(_T("Triune_Cultists"));
	AddComponent(pBufferCom);

	// WeaponBone
	CDynamicMesh*	pDynamicMesh = (CDynamicMesh*)pBufferCom->m_BufferVec[0];
	m_WeaponBone.pFrame = (MeshFrame*)D3DXFrameFind(pDynamicMesh->m_pRootFrame, "right_weapon");
}

CTriune_Cultists::~CTriune_Cultists()
{
	Release();
}

void CTriune_Cultists::Initialize()
{
	CMonster::Initialize();
}

int CTriune_Cultists::Update()
{
	CMonster::Update();

	m_WeaponBone.mWorld = m_WeaponBone.pFrame->mCombinedMatrix * m_pTransformCom->m_mWorld;

	return 0;
}

void CTriune_Cultists::Render()
{
	CMonster::Update();
}

void CTriune_Cultists::Release()
{
}

void CTriune_Cultists::CreateAttack()
{
	if(m_pCollisionCom == NULL)
		return;

	switch(m_pState->GetStateType())
	{
	case STATE_TYPE_TRIUNE_CULTISTS_ATTACK :
		m_pCollisionCom->m_CollisionVec.push_back(new Collision(COLLISION_ATTACK, &m_WeaponBone.mWorld, &D3DXVECTOR3(0.f, 0.f, 0.f), 20.f, 20.f, 20.f));
		break;
	case STATE_TYPE_TRIUNE_CULTISTS_DEATH :
		break;
	case STATE_TYPE_TRIUNE_CULTISTS_HIT :
		break;
	case STATE_TYPE_TRIUNE_CULTISTS_IDLE :
		break;
	case STATE_TYPE_TRIUNE_CULTISTS_RUN :
		break;
	case STATE_TYPE_TRIUNE_CULTISTS_WALK :
		break;
	}

	// CreateAttack
	CMonster::CreateAttack();
}

void CTriune_Cultists::Damage(CPlayer* _pPlayer)
{
	// PreLife
	int iPreLife = m_stat.iLife;

	// Damage
	CMonster::Damage(_pPlayer);

	// CurLife
	int iCurLife = m_stat.iLife;

	// Death
	if(m_stat.iLife <= 0 && m_pState->GetStateType() != STATE_TYPE_TRIUNE_CULTISTS_DEATH)
	{
		SetState(new CTriune_Cultists_Death);
		return;
	}

	// Hit
	if(iCurLife - iPreLife > m_stat.iMaxLife * 0.3f)
	{
		SetState(new CTriune_Cultists_Hit);
		return;
	}
	else
	{
		if(m_pState != NULL && m_pState->GetStateType() != STATE_TYPE_TRIUNE_CULTISTS_RUN)
		{
			SetState(new CTriune_Cultists_Run(1));
			return;
		}
	}
}

void CTriune_Cultists::Damage(CEffect* _pEffect)
{
	// PreLife
	int iPreLife = m_stat.iLife;

	// Damage
	CMonster::Damage(_pEffect);

	// CurLife
	int iCurLife = m_stat.iLife;

	// Death
	if(m_stat.iLife <= 0 && m_pState->GetStateType() != STATE_TYPE_TRIUNE_CULTISTS_DEATH)
	{
		SetState(new CTriune_Cultists_Death);
		return;
	}

	// Hit
	if(iCurLife - iPreLife > m_stat.iMaxLife * 0.3f)
	{
		SetState(new CTriune_Cultists_Hit);
		return;
	}
	else
	{
		if(m_pState != NULL && m_pState->GetStateType() != STATE_TYPE_TRIUNE_CULTISTS_RUN)
		{
			SetState(new CTriune_Cultists_Run(1));
			return;
		}
	}
}