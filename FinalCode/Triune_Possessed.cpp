#include "StdAfx.h"
#include "Triune_Possessed.h"

CTriune_Possessed::CTriune_Possessed(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, int _iLevel)
: CMonster(_tszObjKey, _eObjType, _iLevel)
{
	// Info
	_tcscpy_s(m_info.tszName, MIN_STR, _T("부정한 노예"));

	// Stat
	m_stat.iLife = m_stat.iMaxLife = _iLevel * 4000;
	m_stat.iStrength = _iLevel * 30;

	// CollisionCom
	m_pCollisionCom = new CCollisionCom(COLL_TYPE_MONSTER, new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 60.0f), new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f));
	m_pCollisionCom->m_CollisionVec.push_back(new Collision(COLLISION_DAMAGE, &m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 50.0f, 0.0f), 30.0f, 80.0f, 30.0f));
	AddComponent(m_pCollisionCom);

	// PathFindCom
	CPathFindCom* pPathFindCom = new CPathFindCom(PATH_TYPE_MONSTER, 80.0f);
	AddComponent(pPathFindCom);

	// BufferCom
	CBufferCom* pBufferCom = new CBufferCom;
	pBufferCom->AddBuffer(_T("Triune_Possessed"));
	AddComponent(pBufferCom);

	// LeftHandBone
	CDynamicMesh*	pDynamicMesh = (CDynamicMesh*)pBufferCom->m_BufferVec[0];
	m_LeftHandBone.pFrame = (MeshFrame*)D3DXFrameFind(pDynamicMesh->m_pRootFrame, "left_index1");
}

CTriune_Possessed::~CTriune_Possessed()
{
	Release();
}

void CTriune_Possessed::Initialize()
{
	CMonster::Initialize();
}

int CTriune_Possessed::Update()
{
	CMonster::Update();

	m_LeftHandBone.mWorld = m_LeftHandBone.pFrame->mCombinedMatrix * m_pTransformCom->m_mWorld;

	return 0;
}

void CTriune_Possessed::Render()
{
	CMonster::Render();
}

void CTriune_Possessed::Release()
{
}

void CTriune_Possessed::CreateAttack()
{
	if(m_pCollisionCom == NULL)
		return;

	switch (m_pState->GetStateType())
	{
	case STATE_TYPE_TRIUNE_POSSESSED_ACTIVATION:
		break;
	case STATE_TYPE_TRIUNE_POSSESSED_ATTACK1:
		m_pCollisionCom->m_CollisionVec.push_back(new Collision(COLLISION_ATTACK, &m_LeftHandBone.mWorld, &D3DXVECTOR3(0.f, 0.f, 0.f), 20.f, 20.f, 20.f));
		break;
	case STATE_TYPE_TRIUNE_POSSESSED_ATTACK2_MIDDLE:
		break;
	case STATE_TYPE_TRIUNE_POSSESSED_ATTACK2_END:
		m_pCollisionCom->m_CollisionVec.push_back(new Collision(COLLISION_ATTACK, &m_LeftHandBone.mWorld, &D3DXVECTOR3(0.f, 0.f, 0.f), 20.f, 20.f, 20.f));
		break;
	case STATE_TYPE_TRIUNE_POSSESSED_DEATH:
		break;
	case STATE_TYPE_TRIUNE_POSSESSED_HIT:
		break;
	case STATE_TYPE_TRIUNE_POSSESSED_IDLE:
		break;
	case STATE_TYPE_TRIUNE_POSSESSED_WALK:
		break;
	}

	// CreateAttack
	CMonster::CreateAttack();
}

void CTriune_Possessed::Damage(CPlayer* _pPlayer)
{
	// PreLife
	int iPreLife = m_stat.iLife;

	// Damage
	CMonster::Damage(_pPlayer);

	// CurLife
	int iCurLife = m_stat.iLife;

	// Death
	if(m_stat.iLife <= 0 && m_pState->GetStateType() != STATE_TYPE_TRIUNE_POSSESSED_DEATH)
	{
		SetState(new CTriune_Possessed_Death);
		return;
	}

	// Hit
	if(iCurLife - iPreLife > m_stat.iMaxLife * 0.3f)
	{
		SetState(new CTriune_Possessed_Hit);
		return;
	}
	else
	{
		if(m_pState != NULL && m_pState->GetStateType() != STATE_TYPE_TRIUNE_POSSESSED_WALK)
		{
			SetState(new CTriune_Possessed_Walk(2));
			return;
		}
	}
}

void CTriune_Possessed::Damage(CEffect* _pEffect)
{
	// PreLife
	int iPreLife = m_stat.iLife;

	// Damage
	CMonster::Damage(_pEffect);

	// CurLife
	int iCurLife = m_stat.iLife;

	// Death
	if(m_stat.iLife <= 0 && m_pState->GetStateType() != STATE_TYPE_TRIUNE_POSSESSED_DEATH)
	{
		SetState(new CTriune_Possessed_Death);
		return;
	}

	// Hit
	if(iCurLife - iPreLife > m_stat.iMaxLife * 0.3f)
	{
		SetState(new CTriune_Possessed_Hit);
		return;
	}
	else
	{
		if(m_pState != NULL && m_pState->GetStateType() != STATE_TYPE_TRIUNE_POSSESSED_WALK)
		{
			SetState(new CTriune_Possessed_Walk(2));
			return;
		}
	}
}