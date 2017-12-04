#include "StdAfx.h"
#include "Butcher.h"

CButcher::CButcher(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, int _iLevel)
: CMonster(_tszObjKey, _eObjType, _iLevel)
{
	// Info
	_tcscpy_s(m_info.tszName, MIN_STR, _T("µµ»ìÀÚ"));

	// Stat
	m_stat.iLife = m_stat.iMaxLife = _iLevel * 1000;
	m_stat.iStrength = _iLevel * 5;

	// CollisionCom
	m_pCollisionCom = new CCollisionCom(COLL_TYPE_MONSTER, new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 60.0f), new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 60.0f));
	m_pCollisionCom->m_CollisionVec.push_back(new Collision(COLLISION_DAMAGE, &m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 50.0f, 0.0f), 70.0f, 100.0f, 70.0f));
	AddComponent(m_pCollisionCom);

	// PathFindCom
	CPathFindCom* pPathFindCom = new CPathFindCom(PATH_TYPE_MONSTER, 120.0f);
	AddComponent(pPathFindCom);

	// BufferCom
	CBufferCom* pBufferCom = new CBufferCom;
	pBufferCom->AddBuffer(_T("Butcher"));
	AddComponent(pBufferCom);

	// WeaponBone
	CDynamicMesh*	pDynamicMesh = (CDynamicMesh*)pBufferCom->m_BufferVec[0];
	m_RightWeaponBone.pFrame = (MeshFrame*)D3DXFrameFind(pDynamicMesh->m_pRootFrame, "right_weapon");
	m_LeftWeaponBone.pFrame = (MeshFrame*)D3DXFrameFind(pDynamicMesh->m_pRootFrame, "left_weapon");
	m_CenterBone.pFrame = (MeshFrame*)D3DXFrameFind(pDynamicMesh->m_pRootFrame, "Spine2");
}

CButcher::~CButcher()
{
	Release();
}

void CButcher::Initialize()
{
	CMonster::Initialize();
}

int CButcher::Update()
{
	CMonster::Update();

	m_RightWeaponBone.mWorld = m_RightWeaponBone.pFrame->mCombinedMatrix * m_pTransformCom->m_mWorld;
	m_LeftWeaponBone.mWorld = m_LeftWeaponBone.pFrame->mCombinedMatrix * m_pTransformCom->m_mWorld;
	m_CenterBone.mWorld = m_CenterBone.pFrame->mCombinedMatrix * m_pTransformCom->m_mWorld;

	return 0;
}

void CButcher::Render()
{
	CMonster::Render();
}

void CButcher::Release()
{
}

void CButcher::CreateAttack()
{
	if(m_pCollisionCom == NULL)
		return;

	switch(m_pState->GetStateType())
	{
	case STATE_TYPE_BUTCHER_ATTACK1 :
		m_pCollisionCom->m_CollisionVec.push_back(new Collision(COLLISION_ATTACK, &m_RightWeaponBone.mWorld, &D3DXVECTOR3(0.f, 0.f, 0.f), 20.f, 20.f, 20.f));
		break;
	case STATE_TYPE_BUTCHER_ATTACK2 :
		m_pCollisionCom->m_CollisionVec.push_back(new Collision(COLLISION_ATTACK, &m_LeftWeaponBone.mWorld, &D3DXVECTOR3(0.f, 0.f, 0.f), 20.f, 20.f, 20.f));
		break;
	case STATE_TYPE_BUTCHER_CHAIN_IN :
		break;
	case STATE_TYPE_BUTCHER_CHAIN_OUT :
		break;
	case STATE_TYPE_BUTCHER_CHARGE_IN :
		break;
	case STATE_TYPE_BUTCHER_DEATH :
		break;
	case STATE_TYPE_BUTCHER_FAN_OF_CHAINS :
		break;
	case STATE_TYPE_BUTCHER_IDLE :
		break;
	case STATE_TYPE_BUTCHER_INTRO :
		break;
	case STATE_TYPE_BUTCHER_INTRO_WALK :
		break;
	case STATE_TYPE_BUTCHER_PHASE_CHANGE :
		break;
	case STATE_TYPE_BUTCHER_PULL_ATTACK :
		m_pCollisionCom->m_CollisionVec.push_back(new Collision(COLLISION_ATTACK, &m_RightWeaponBone.mWorld, &D3DXVECTOR3(0.f, 0.f, 0.f), 20.f, 20.f, 20.f));
		break;
	case STATE_TYPE_BUTCHER_RUN :
		m_pCollisionCom->m_CollisionVec.push_back(new Collision(COLLISION_ATTACK, &m_CenterBone.mWorld, &D3DXVECTOR3(0.f, 0.f, 0.f), 70.f, 70.f, 70.f));
		break;
	case STATE_TYPE_BUTCHER_STUNNED :
		break;
	case STATE_TYPE_BUTCHER_WALK :
		break;
	}

	// CreateAttack
	CMonster::CreateAttack();
}

void CButcher::Damage(CPlayer* _pPlayer)
{
	// Damage
	CMonster::Damage(_pPlayer);

	// Death
	if(m_stat.iLife <= 0 && m_pState->GetStateType() != STATE_TYPE_BUTCHER_DEATH)
	{
		SetState(new CButcher_Death);
		return;
	}
}

void CButcher::Damage(CEffect* _pEffect)
{
	// Damage
	CMonster::Damage(_pEffect);

	// Death
	if(m_stat.iLife <= 0 && m_pState->GetStateType() != STATE_TYPE_BUTCHER_DEATH)
	{
		SetState(new CButcher_Death);
		return;
	}
}