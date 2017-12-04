#include "StdAfx.h"
#include "Warden.h"

CWarden::CWarden(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, int _iLevel)
: CMonster(_tszObjKey, _eObjType, _iLevel)
{
	// Info
	_tcscpy_s(m_info.tszName, MIN_STR, _T("±³µµ°ü"));

	// Stat
	m_stat.iLife = m_stat.iMaxLife = 15000000;
	m_stat.iStrength = 5000;

	// CollisionCom
	m_pCollisionCom = new CCollisionCom(COLL_TYPE_MONSTER, new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 60.0f), new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f));
	m_pCollisionCom->m_CollisionVec.push_back(new Collision(COLLISION_DAMAGE, &m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 30.0f, 0.0f), 20.0f, 40.0f, 20.0f));
	AddComponent(m_pCollisionCom);

	// PathFindCom
	CPathFindCom* pPathFindCom = new CPathFindCom(PATH_TYPE_MONSTER, 200.0f);
	AddComponent(pPathFindCom);

	// BufferCom
	CBufferCom* pBufferCom = new CBufferCom;
	pBufferCom->AddBuffer(_T("Warden"));
	AddComponent(pBufferCom);

	// WeaponBone
	CDynamicMesh*	pDynamicMesh = (CDynamicMesh*)pBufferCom->m_BufferVec[0];
	m_WeaponBone.pFrame = (MeshFrame*)D3DXFrameFind(pDynamicMesh->m_pRootFrame, "right_weapon");
}

CWarden::~CWarden()
{
	Release();
}

void CWarden::Initialize()
{
	CMonster::Initialize();
}

int CWarden::Update()
{
	CMonster::Update();

	m_WeaponBone.mWorld = m_WeaponBone.pFrame->mCombinedMatrix * m_pTransformCom->m_mWorld;

	return 0;
}

void CWarden::Render()
{
	CMonster::Update();
}

void CWarden::Release()
{
}

void CWarden::CreateAttack()
{
	if(m_pCollisionCom == NULL)
		return;

	switch(m_pState->GetStateType())
	{
	case STATE_TYPE_WARDEN_ATTACK1 :
		m_pCollisionCom->m_CollisionVec.push_back(new Collision(COLLISION_ATTACK, &m_WeaponBone.mWorld, &D3DXVECTOR3(0.f, 0.f, -20.f), 20.f, 20.f, 20.f));
		break;
	case STATE_TYPE_WARDEN_ATTACK2 :
		break;
	case STATE_TYPE_WARDEN_DEATH :
		break;
	case STATE_TYPE_WARDEN_HIT :
		break;
	case STATE_TYPE_WARDEN_IDLE :
		break;
	case STATE_TYPE_WARDEN_RUN :
		break;
	}

	// CreateAttack
	CMonster::CreateAttack();
}

void CWarden::Damage(CPlayer* _pPlayer)
{
	// PreLife
	int iPreLife = m_stat.iLife;

	// Damage
	CMonster::Damage(_pPlayer);

	// CurLife
	int iCurLife = m_stat.iLife;

	// Death
	if(m_stat.iLife <= 0 && m_pState->GetStateType() != STATE_TYPE_WARDEN_DEATH)
	{
		// DynamicProbVec
		vector<CObject*> DynamicProbVec;
		m_pLayer->FindObjects(DynamicProbVec, _T("DynamicProb"), LAYER_TYPE_DYNAMIC_PROB);

		for(size_t i = 0; i < DynamicProbVec.size(); ++i)
		{
			CDynamicProb* pDynamicProb = (CDynamicProb*)DynamicProbVec[i];
			if(pDynamicProb->GetProbType() == PROB_TYPE_ROYAL_CHAMBER_TO_REORIK_MANSION)
			{
				pDynamicProb->Event();
				break;
			}
		}

		SetState(new CWarden_Death);
		return;
	}

	// Hit
	if(iCurLife - iPreLife > m_stat.iMaxLife * 0.3f)
	{
		SetState(new CWarden_Hit);
		return;
	}
	else
	{
		if(m_pState != NULL && m_pState->GetStateType() != STATE_TYPE_WARDEN_RUN)
		{
			SetState(new CWarden_Run(2));
			return;
		}
	}
}

void CWarden::Damage(CEffect* _pEffect)
{
	// PreLife
	int iPreLife = m_stat.iLife;

	// Damage
	CMonster::Damage(_pEffect);

	// CurLife
	int iCurLife = m_stat.iLife;

	// Death
	if(m_stat.iLife <= 0 && m_pState->GetStateType() != STATE_TYPE_WARDEN_DEATH)
	{
		// DynamicProbVec
		vector<CObject*> DynamicProbVec;
		m_pLayer->FindObjects(DynamicProbVec, _T("DynamicProb"), LAYER_TYPE_DYNAMIC_PROB);

		for(size_t i = 0; i < DynamicProbVec.size(); ++i)
		{
			CDynamicProb* pDynamicProb = (CDynamicProb*)DynamicProbVec[i];
			if(pDynamicProb->GetProbType() == PROB_TYPE_ROYAL_CHAMBER_TO_REORIK_MANSION)
			{
				pDynamicProb->Event();
				break;
			}
		}

		SetState(new CWarden_Death);
		return;
	}

	// Hit
	if(iCurLife - iPreLife > m_stat.iMaxLife * 0.3f)
	{
		SetState(new CWarden_Hit);
		return;
	}
}