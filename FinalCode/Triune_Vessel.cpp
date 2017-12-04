#include "StdAfx.h"
#include "Triune_Vessel.h"

CTriune_Vessel::CTriune_Vessel(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, int _iLevel)
: CMonster(_tszObjKey, _eObjType, _iLevel)
{
	// Info
	_tcscpy_s(m_info.tszName, MIN_STR, _T("¾îµÒÀÇ À°½Å"));

	// Stat
	m_stat.iLife = m_stat.iMaxLife = _iLevel * 4000;
	m_stat.iStrength = _iLevel * 30;

	// CollisionCom
	m_pCollisionCom = new CCollisionCom(COLL_TYPE_MONSTER, new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 60.0f), new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 30.0f));
	m_pCollisionCom->m_CollisionVec.push_back(new Collision(COLLISION_DAMAGE, &m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 50.0f, 0.0f), 20.0f, 60.0f, 20.0f));
	AddComponent(m_pCollisionCom);

	// PathFindCom
	CPathFindCom* pPathFindCom = new CPathFindCom(PATH_TYPE_MONSTER, 60.0f);
	AddComponent(pPathFindCom);

	// BufferCom
	CBufferCom* pBufferCom = new CBufferCom;
	pBufferCom->AddBuffer(_T("Triune_Vessel"));
	AddComponent(pBufferCom);

}

CTriune_Vessel::~CTriune_Vessel()
{
	Release();
}

void CTriune_Vessel::Initialize()
{
	CMonster::Initialize();
}

int CTriune_Vessel::Update()
{
	CMonster::Update();

	return 0;
}

void CTriune_Vessel::Render()
{
	CMonster::Update();
}

void CTriune_Vessel::Release()
{
}

void CTriune_Vessel::CreateAttack()
{
	if(m_pCollisionCom == NULL)
		return;

	switch(m_pState->GetStateType())
	{
	case STATE_TYPE_TRIUNE_VESSEL_ACTIVATING :
		break;
	case STATE_TYPE_TRIUNE_VESSEL_ACTIVATION :
		break;
	case STATE_TYPE_TRIUNE_VESSEL_DEATH :
		break;
	case STATE_TYPE_TRIUNE_VESSEL_HIT :
		break;
	case STATE_TYPE_TRIUNE_VESSEL_IDLE :
		break;
	case STATE_TYPE_TRIUNE_VESSEL_WALK :
		break;
	}

	// CreateAttack
	CMonster::CreateAttack();
}

void CTriune_Vessel::Damage(CPlayer* _pPlayer)
{
	// PreLife
	int iPreLife = m_stat.iLife;

	// Damage
	CMonster::Damage(_pPlayer);

	// CurLife
	int iCurLife = m_stat.iLife;

	// Death
	if(m_stat.iLife <= 0 && m_pState->GetStateType() != STATE_TYPE_TRIUNE_VESSEL_DEATH)
	{
		SetState(new CTriune_Vessel_Death);
		return;
	}

	// Hit
	if(iCurLife - iPreLife > m_stat.iMaxLife * 0.3f)
	{
		SetState(new CTriune_Vessel_Hit);
		return;
	}
}

void CTriune_Vessel::Damage(CEffect* _pEffect)
{
	// PreLife
	int iPreLife = m_stat.iLife;

	// Damage
	CMonster::Damage(_pEffect);

	// CurLife
	int iCurLife = m_stat.iLife;

	// Death
	if(m_stat.iLife <= 0 && m_pState->GetStateType() != STATE_TYPE_TRIUNE_VESSEL_DEATH)
	{
		SetState(new CTriune_Vessel_Death);
		return;
	}

	// Hit
	if(iCurLife - iPreLife > m_stat.iMaxLife * 0.3f)
	{
		SetState(new CTriune_Vessel_Hit);
		return;
	}
}