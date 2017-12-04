#include "StdAfx.h"
#include "Zombie_Skinny_Male_White.h"

CZombie_Skinny_Male_White::CZombie_Skinny_Male_White(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, int _iLevel)
: CMonster(_tszObjKey, _eObjType, _iLevel)
{
	// Info
	_tcscpy_s(m_info.tszName, MIN_STR, _T("되살아난 자"));

	// Stat
	m_stat.iLife = m_stat.iMaxLife = _iLevel * 80;
	m_stat.iStrength = _iLevel * 2;

	// CollisionCom
	m_pCollisionCom = new CCollisionCom(COLL_TYPE_MONSTER, new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 60.0f), new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 25.0f));
	m_pCollisionCom->m_CollisionVec.push_back(new Collision(COLLISION_DAMAGE, &m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 50.0f, 0.0f), 20.0f, 50.0f, 20.0f));
	AddComponent(m_pCollisionCom);

	// PathFindCom
	CPathFindCom* pPathFindCom = new CPathFindCom(PATH_TYPE_MONSTER, 80.0f);
	AddComponent(pPathFindCom);

	// BufferCom
	CBufferCom* pBufferCom = new CBufferCom;
	pBufferCom->AddBuffer(_T("Zombie_Skinny_Male_White"));
	AddComponent(pBufferCom);

	// Bone
	CDynamicMesh*	pDynamicMesh = (CDynamicMesh*)pBufferCom->m_BufferVec[0];
	// LeftHandBone
	m_LeftHandBone.pFrame = (MeshFrame*)D3DXFrameFind(pDynamicMesh->m_pRootFrame, "left_middle1");
	// RightHandBone
	m_RightHandBone.pFrame = (MeshFrame*)D3DXFrameFind(pDynamicMesh->m_pRootFrame, "right_middle1");
	// HeadBone
	m_HeadBone.pFrame = (MeshFrame*)D3DXFrameFind(pDynamicMesh->m_pRootFrame, "Head");
}

CZombie_Skinny_Male_White::~CZombie_Skinny_Male_White()
{
	Release();
}

void CZombie_Skinny_Male_White::Initialize()
{
	CMonster::Initialize();
}

int CZombie_Skinny_Male_White::Update()
{
	CMonster::Update();

	m_LeftHandBone.mWorld = m_LeftHandBone.pFrame->mCombinedMatrix * m_pTransformCom->m_mWorld;
	m_RightHandBone.mWorld = m_RightHandBone.pFrame->mCombinedMatrix * m_pTransformCom->m_mWorld;
	m_HeadBone.mWorld = m_HeadBone.pFrame->mCombinedMatrix * m_pTransformCom->m_mWorld;

	return 0;
}

void CZombie_Skinny_Male_White::Render()
{
	CMonster::Render();
}

void CZombie_Skinny_Male_White::Release()
{
}

void CZombie_Skinny_Male_White::CreateAttack()
{
	if(m_pCollisionCom == NULL)
		return;

	switch(m_pState->GetStateType())
	{
	case STATE_TYPE_ZOMBIE_SKINNY_MALE_WHITE_ATTACK1:
		m_pCollisionCom->m_CollisionVec.push_back(new Collision(COLLISION_ATTACK, &m_RightHandBone.mWorld, &D3DXVECTOR3(0.f, 0.f, 0.f), 20.f, 20.f, 20.f));
		break;
	case STATE_TYPE_ZOMBIE_SKINNY_MALE_WHITE_ATTACK2:
		m_pCollisionCom->m_CollisionVec.push_back(new Collision(COLLISION_ATTACK, &m_RightHandBone.mWorld, &D3DXVECTOR3(0.f, 0.f, 0.f), 20.f, 20.f, 20.f));
		break;
	case STATE_TYPE_ZOMBIE_SKINNY_MALE_WHITE_ATTACK3:
		m_pCollisionCom->m_CollisionVec.push_back(new Collision(COLLISION_ATTACK, &m_LeftHandBone.mWorld, &D3DXVECTOR3(0.f, 0.f, 0.f), 20.f, 20.f, 20.f));
		break;
	case STATE_TYPE_ZOMBIE_SKINNY_MALE_WHITE_ATTACK4:
		m_pCollisionCom->m_CollisionVec.push_back(new Collision(COLLISION_ATTACK, &m_HeadBone.mWorld, &D3DXVECTOR3(0.f, 0.f, 0.f), 20.f, 20.f, 20.f));
		break;
	case STATE_TYPE_ZOMBIE_SKINNY_MALE_WHITE_DEATH:
		break;
	case STATE_TYPE_ZOMBIE_SKINNY_MALE_WHITE_HIT:
		break;
	case STATE_TYPE_ZOMBIE_SKINNY_MALE_WHITE_IDLE:
		break;
	case STATE_TYPE_ZOMBIE_SKINNY_MALE_WHITE_WALK1:
		break;
	case STATE_TYPE_ZOMBIE_SKINNY_MALE_WHITE_SPAWN:
		break;
	}

	// CreateAttack
	CMonster::CreateAttack();
}

void CZombie_Skinny_Male_White::Damage(CPlayer* _pPlayer)
{
	// PreLife
	int iPreLife = m_stat.iLife;

	// Damage
	CMonster::Damage(_pPlayer);

	// CurLife
	int iCurLife = m_stat.iLife;

	// Death
	if(m_stat.iLife <= 0 && m_pState->GetStateType() != STATE_TYPE_ZOMBIE_SKINNY_MALE_WHITE_DEATH)
	{
		SetState(new CZombie_Skinny_Male_White_Death);

		if(rand() % 100 > 90)
			DropZombieEyeBlue();

		return;
	}

	// Hit
	if(iCurLife - iPreLife > m_stat.iMaxLife * 0.3f)
	{
		SetState(new CZombie_Skinny_Male_White_Hit);
		return;
	}
	else
	{
		if(m_pState != NULL && m_pState->GetStateType() != STATE_TYPE_ZOMBIE_SKINNY_MALE_WHITE_WALK1)
		{
			SetState(new CZombie_Skinny_Male_White_Walk1(3));
			return;
		}
	}
}

void CZombie_Skinny_Male_White::Damage(CEffect* _pEffect)
{
	// PreLife
	int iPreLife = m_stat.iLife;

	// Damage
	CMonster::Damage(_pEffect);

	// CurLife
	int iCurLife = m_stat.iLife;

	// Death
	if(m_stat.iLife <= 0 && m_pState->GetStateType() != STATE_TYPE_ZOMBIE_SKINNY_MALE_WHITE_DEATH)
	{
		SetState(new CZombie_Skinny_Male_White_Death);

		if(rand() % 100 > 90)
			DropZombieEyeBlue();

		return;
	}

	// Hit
	if(iCurLife - iPreLife > m_stat.iMaxLife * 0.3f)
	{
		SetState(new CZombie_Skinny_Male_White_Hit);
		return;
	}
	else
	{
		if(m_pState != NULL && m_pState->GetStateType() != STATE_TYPE_ZOMBIE_SKINNY_MALE_WHITE_WALK1)
		{
			SetState(new CZombie_Skinny_Male_White_Walk1(3));
			return;
		}
	}
}

void CZombie_Skinny_Male_White::DropZombieEyeBlue()
{
	Item* pItem = new Item(_T("좀비눈알(청)"), _T("Item_Quest_7"), NULL, 0, ITEM_TYPE_QUEST, QUEST_ID_7, -1, -1, 1, 1, 2, 0, 1000, 1, 0, 0);
	CDropItem* pDropItem = new CDropItem(_T("Item"), OBJ_TYPE_DYNAMIC, pItem);
	m_pLayer->AddObject(pDropItem, LAYER_TYPE_DROP);

	CTransformCom* pTransformCom = (CTransformCom*)pDropItem->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = m_pTransformCom->m_vPos;

	pDropItem->Initialize();
}