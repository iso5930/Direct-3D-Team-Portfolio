#include "StdAfx.h"
#include "Zombie_Male.h"

CZombie_Male::CZombie_Male(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, int _iLevel)
: CMonster(_tszObjKey, _eObjType, _iLevel)
{
	// Info
	_tcscpy_s(m_info.tszName, MIN_STR, _T("걸어다니는 시체"));

	// Stat
	m_stat.iLife = m_stat.iMaxLife = _iLevel * 100;
	m_stat.iStrength = _iLevel * 2;

	// CollisionCom
	m_pCollisionCom = new CCollisionCom(COLL_TYPE_MONSTER, new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 60.0f),  new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 30.0f));
	m_pCollisionCom->m_CollisionVec.push_back(new Collision(COLLISION_DAMAGE, &m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.f, 50.0f, 0.0f), 20.0f, 50.0f, 20.0f));
	AddComponent(m_pCollisionCom);

	// PathFindCom
	CPathFindCom* pPathFindCom = new CPathFindCom(PATH_TYPE_MONSTER, 30.0f);
	AddComponent(pPathFindCom);

	CBufferCom*	pBufferCom = new CBufferCom;
	pBufferCom->AddBuffer(_T("Zombie_Male"));
	AddComponent(pBufferCom);

	// RightHandBone
	CDynamicMesh*	pDynamicMesh = (CDynamicMesh*)pBufferCom->m_BufferVec[0];
	m_RightHandBone.pFrame = (MeshFrame*)D3DXFrameFind(pDynamicMesh->m_pRootFrame, "right_index1");
}

CZombie_Male::~CZombie_Male()
{
	Release();
}

void CZombie_Male::Initialize()
{
	CMonster::Initialize();
}

int CZombie_Male::Update()
{
	CMonster::Update();

	m_RightHandBone.mWorld = m_RightHandBone.pFrame->mCombinedMatrix * m_pTransformCom->m_mWorld;

	return 0;
}

void CZombie_Male::Render()
{
	CMonster::Render();
}

void CZombie_Male::Release()
{
}

void CZombie_Male::CreateAttack()
{
	if(m_pCollisionCom == NULL)
		return;

	switch(m_pState->GetStateType())
	{
	case STATE_TYPE_ZOMBIE_MALE_ATTACK:
		m_pCollisionCom->m_CollisionVec.push_back(new Collision(COLLISION_ATTACK, &m_RightHandBone.mWorld, &D3DXVECTOR3(0.f, 0.f, 0.f), 20.f, 20.f, 20.f));
		break;
	case STATE_TYPE_ZOMBIE_MALE_DEATH:
		break;
	case STATE_TYPE_ZOMBIE_MALE_HIT:
		break;
	case STATE_TYPE_ZOMBIE_MALE_IDLE:
		break;
	case STATE_TYPE_ZOMBIE_MALE_WALK:
		break;
	}

	// CreateAttack
	CMonster::CreateAttack();
}

void CZombie_Male::Damage(CPlayer* _pPlayer)
{
	// PreLife
	int iPreLife = m_stat.iLife;

	// Damage
	CMonster::Damage(_pPlayer);

	// CurLife
	int iCurLife = m_stat.iLife;

	// Death
	if(m_stat.iLife <= 0 && m_pState->GetStateType() != STATE_TYPE_ZOMBIE_MALE_DEATH)
	{
		SetState(new CZombie_Male_Death);

		if(rand() % 100 > 90)
			DropZombieEyeBlue();

		return;
	}

	// Hit
	if(iCurLife - iPreLife > m_stat.iMaxLife * 0.3f)
	{
		SetState(new CZombie_Male_Hit);
		return;
	}
	else
	{
		if(m_pState != NULL && m_pState->GetStateType() != STATE_TYPE_ZOMBIE_MALE_WALK)
		{
			SetState(new CZombie_Male_Walk(3));
			return;
		}
	}
}

void CZombie_Male::Damage(CEffect* _pEffect)
{
	// PreLife
	int iPreLife = m_stat.iLife;

	// Damage
	CMonster::Damage(_pEffect);

	// CurLife
	int iCurLife = m_stat.iLife;

	// Death
	if(m_stat.iLife <= 0 && m_pState->GetStateType() != STATE_TYPE_ZOMBIE_MALE_DEATH)
	{
		SetState(new CZombie_Male_Death);

		if(rand() % 100 > 90)
			DropZombieEyeBlue();

		return;
	}

	// Hit
	if(iCurLife - iPreLife > m_stat.iMaxLife * 0.3f)
	{
		SetState(new CZombie_Male_Hit);
		return;
	}
	else
	{
		if(m_pState != NULL && m_pState->GetStateType() != STATE_TYPE_ZOMBIE_MALE_WALK)
		{
			SetState(new CZombie_Male_Walk(3));
			return;
		}
	}
}

void CZombie_Male::DropZombieEyeBlue()
{
	Item* pItem = new Item(_T("좀비눈알(청)"), _T("Item_Quest_7"), NULL, 0, ITEM_TYPE_QUEST, QUEST_ID_7, -1, -1, 1, 1, 2, 0, 1000, 1, 0, 0);
	CDropItem* pDropItem = new CDropItem(_T("Item"), OBJ_TYPE_DYNAMIC, pItem);
	m_pLayer->AddObject(pDropItem, LAYER_TYPE_DROP);

	CTransformCom* pTransformCom = (CTransformCom*)pDropItem->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = m_pTransformCom->m_vPos;

	pDropItem->Initialize();
}