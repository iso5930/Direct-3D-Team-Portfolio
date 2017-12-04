#include "StdAfx.h"
#include "Triune_Berserker.h"

CTriune_Berserker::CTriune_Berserker(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, int _iLevel)
: CMonster(_tszObjKey, _eObjType, _iLevel)
{
	// Info
	_tcscpy_s(m_info.tszName, MIN_STR, _T("¾îµÒÀÇ ±¤Àü»ç"));

	// Stat
	m_stat.iLife = m_stat.iMaxLife = _iLevel * 16000;
	m_stat.iStrength = _iLevel * 50;

	// CollisionCom
	m_pCollisionCom = new CCollisionCom(COLL_TYPE_MONSTER, new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 60.0f), new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 30.0f));
	m_pCollisionCom->m_CollisionVec.push_back(new Collision(COLLISION_DAMAGE, &m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 50.0f, 0.0f), 30.0f, 60.0f, 30.0f));
	AddComponent(m_pCollisionCom);

	// PathFindCom
	CPathFindCom* pPathFindCom = new CPathFindCom(PATH_TYPE_MONSTER, 240.0f);
	AddComponent(pPathFindCom);

	// BufferCom
	CBufferCom* pBufferCom = new CBufferCom;
	pBufferCom->AddBuffer(_T("Triune_Berserker"));
	AddComponent(pBufferCom);

	// WeaponBone
	CDynamicMesh*	pDynamicMesh = (CDynamicMesh*)pBufferCom->m_BufferVec[0];
	m_WeaponBone.pFrame = (MeshFrame*)D3DXFrameFind(pDynamicMesh->m_pRootFrame, "right_weapon");
}

CTriune_Berserker::~CTriune_Berserker()
{
	Release();
}

void CTriune_Berserker::Initialize()
{
	CMonster::Initialize();
}

int CTriune_Berserker::Update()
{
	CMonster::Update();

	m_WeaponBone.mWorld = m_WeaponBone.pFrame->mCombinedMatrix * m_pTransformCom->m_mWorld;

	return 0;
}

void CTriune_Berserker::Render()
{
	CMonster::Render();
}

void CTriune_Berserker::Release()
{
}

void CTriune_Berserker::CreateAttack()
{
	if(m_pCollisionCom == NULL)
		return;

	switch(m_pState->GetStateType())
	{
	case STATE_TYPE_TRIUNE_BERSERKER_ATTACK1 :
		m_pCollisionCom->m_CollisionVec.push_back(new Collision(COLLISION_ATTACK, &m_WeaponBone.mWorld, &D3DXVECTOR3(0.f, 0.f, 0.f), 20.f, 20.f, 20.f));
		break;
	case STATE_TYPE_TRIUNE_BERSERKER_ATTACK2 :
		m_pCollisionCom->m_CollisionVec.push_back(new Collision(COLLISION_ATTACK, &m_WeaponBone.mWorld, &D3DXVECTOR3(0.f, 0.f, 0.f), 20.f, 20.f, 20.f));
		break;
	case STATE_TYPE_TRIUNE_BERSERKER_DEATH :
		break;
	case STATE_TYPE_TRIUNE_BERSERKER_HIT :
		break;
	case STATE_TYPE_TRIUNE_BERSERKER_IDLE :
		break;
	case STATE_TYPE_TRIUNE_BERSERKER_RUN :
		break;
	}

	// CreateAttack
	CMonster::CreateAttack();
}

void CTriune_Berserker::Damage(CPlayer* _pPlayer)
{
	// PreLife
	int iPreLife = m_stat.iLife;

	// Damage
	CMonster::Damage(_pPlayer);

	// CurLife
	int iCurLife = m_stat.iLife;

	// Death
	if(m_stat.iLife <= 0 && m_pState->GetStateType() != STATE_TYPE_TRIUNE_BERSERKER_DEATH)
	{
		SetState(new CTriune_Berserker_Death);
		return;
	}

	// Hit
	if(iCurLife - iPreLife > m_stat.iMaxLife * 0.3f)
	{
		SetState(new CTriune_Berserker_Hit);
		return;
	}
	else
	{
		if(m_pState != NULL && m_pState->GetStateType() != STATE_TYPE_TRIUNE_BERSERKER_RUN)
		{
			SetState(new CTriune_Berserker_Run(2));
			return;
		}
	}
}

void CTriune_Berserker::Damage(CEffect* _pEffect)
{
	// PreLife
	int iPreLife = m_stat.iLife;

	// Damage
	CMonster::Damage(_pEffect);

	// CurLife
	int iCurLife = m_stat.iLife;

	// Death
	if(m_stat.iLife <= 0 && m_pState->GetStateType() != STATE_TYPE_TRIUNE_BERSERKER_DEATH)
	{
		SetState(new CTriune_Berserker_Death);
		return;
	}

	// Hit
	if(iCurLife - iPreLife > m_stat.iMaxLife * 0.3f)
	{
		SetState(new CTriune_Berserker_Hit);
		return;
	}
	else
	{
		if(m_pState != NULL && m_pState->GetStateType() != STATE_TYPE_TRIUNE_BERSERKER_RUN)
		{
			SetState(new CTriune_Berserker_Run(2));
			return;
		}
	}
}