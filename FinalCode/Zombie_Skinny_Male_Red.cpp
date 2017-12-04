#include "StdAfx.h"
#include "Zombie_Skinny_Male_Red.h"

CZombie_Skinny_Male_Red::CZombie_Skinny_Male_Red(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, int _iLevel)
: CMonster(_tszObjKey, _eObjType, _iLevel)
{
	// Info
	_tcscpy_s(m_info.tszName, MIN_STR, _T("Áö¿ÁºÒ Á»ºñ"));

	// Stat
	m_stat.iLife = m_stat.iMaxLife = _iLevel * 4000;
	m_stat.iStrength = _iLevel * 30;

	// CollisionCom
	m_pCollisionCom = new CCollisionCom(COLL_TYPE_MONSTER, new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 60.0f), new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 30.0f));
	m_pCollisionCom->m_CollisionVec.push_back(new Collision(COLLISION_DAMAGE, &m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 50.0f, 0.0f), 20.0f, 50.0f, 20.0f));
	AddComponent(m_pCollisionCom);

	// PathFindCom
	CPathFindCom* pPathFindCom = new CPathFindCom(PATH_TYPE_MONSTER, 80.0f);
	AddComponent(pPathFindCom);

	// BufferCom
	CBufferCom* pBufferCom = new CBufferCom;
	pBufferCom->AddBuffer(_T("Zombie_Skinny_Male_Red"));
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

CZombie_Skinny_Male_Red::~CZombie_Skinny_Male_Red()
{
	Release();
}

void CZombie_Skinny_Male_Red::Initialize()
{
	CMonster::Initialize();
}

int CZombie_Skinny_Male_Red::Update()
{
	CMonster::Update();

	m_LeftHandBone.mWorld = m_LeftHandBone.pFrame->mCombinedMatrix * m_pTransformCom->m_mWorld;
	m_RightHandBone.mWorld = m_RightHandBone.pFrame->mCombinedMatrix * m_pTransformCom->m_mWorld;
	m_HeadBone.mWorld = m_HeadBone.pFrame->mCombinedMatrix * m_pTransformCom->m_mWorld;

	return 0;
}

void CZombie_Skinny_Male_Red::Render()
{
	CMonster::Render();
}

void CZombie_Skinny_Male_Red::Release()
{
}

void CZombie_Skinny_Male_Red::CreateAttack()
{
	if(m_pCollisionCom == NULL)
		return;

	switch(m_pState->GetStateType())
	{
	case STATE_TYPE_ZOMBIE_SKINNY_MALE_RED_ATTACK1:
		m_pCollisionCom->m_CollisionVec.push_back(new Collision(COLLISION_ATTACK, &m_RightHandBone.mWorld, &D3DXVECTOR3(0.f, 0.f, 0.f), 20.f, 20.f, 20.f));
		break;
	case STATE_TYPE_ZOMBIE_SKINNY_MALE_RED_ATTACK2:
		m_pCollisionCom->m_CollisionVec.push_back(new Collision(COLLISION_ATTACK, &m_RightHandBone.mWorld, &D3DXVECTOR3(0.f, 0.f, 0.f), 20.f, 20.f, 20.f));
		break;
	case STATE_TYPE_ZOMBIE_SKINNY_MALE_RED_ATTACK3:
		m_pCollisionCom->m_CollisionVec.push_back(new Collision(COLLISION_ATTACK, &m_LeftHandBone.mWorld, &D3DXVECTOR3(0.f, 0.f, 0.f), 20.f, 20.f, 20.f));
		break;
	case STATE_TYPE_ZOMBIE_SKINNY_MALE_RED_ATTACK4:
		m_pCollisionCom->m_CollisionVec.push_back(new Collision(COLLISION_ATTACK, &m_HeadBone.mWorld, &D3DXVECTOR3(0.f, 0.f, 0.f), 20.f, 20.f, 20.f));
		break;
	case STATE_TYPE_ZOMBIE_SKINNY_MALE_RED_DEATH:
		break;
	case STATE_TYPE_ZOMBIE_SKINNY_MALE_RED_HIT:
		break;
	case STATE_TYPE_ZOMBIE_SKINNY_MALE_RED_IDLE:
		break;
	case STATE_TYPE_ZOMBIE_SKINNY_MALE_RED_WALK1:
		break;
	case STATE_TYPE_ZOMBIE_SKINNY_MALE_RED_SPAWN:
		break;
	}

	// CreateAttack
	CMonster::CreateAttack();
}

void CZombie_Skinny_Male_Red::Damage(CPlayer* _pPlayer)
{
	// PreLife
	int iPreLife = m_stat.iLife;

	// Damage
	CMonster::Damage(_pPlayer);

	// CurLife
	int iCurLife = m_stat.iLife;

	// Death
	if(m_stat.iLife <= 0 && m_pState->GetStateType() != STATE_TYPE_ZOMBIE_SKINNY_MALE_RED_DEATH)
	{
		SetState(new CZombie_Skinny_Male_Red_Death);

		if(rand() % 100 > 90)
			DropZombieEyeBlue();

		return;
	}

	// Hit
	if(iCurLife - iPreLife > m_stat.iMaxLife * 0.3f)
	{
		SetState(new CZombie_Skinny_Male_Red_Hit);
		return;
	}
	else
	{
		if(m_pState != NULL && m_pState->GetStateType() != STATE_TYPE_ZOMBIE_SKINNY_MALE_RED_WALK1)
		{
			SetState(new CZombie_Skinny_Male_Red_Walk1(2));
			return;
		}
	}
}

void CZombie_Skinny_Male_Red::Damage(CEffect* _pEffect)
{
	// PreLife
	int iPreLife = m_stat.iLife;

	// Damage
	CMonster::Damage(_pEffect);

	// CurLife
	int iCurLife = m_stat.iLife;

	// Death
	if(m_stat.iLife <= 0 && m_pState->GetStateType() != STATE_TYPE_ZOMBIE_SKINNY_MALE_RED_DEATH)
	{
		SetState(new CZombie_Skinny_Male_Red_Death);

		if(rand() % 100 > 90)
			DropZombieEyeBlue();

		return;
	}

	// Hit
	if(iCurLife - iPreLife > m_stat.iMaxLife * 0.3f)
	{
		SetState(new CZombie_Skinny_Male_Red_Hit);
		return;
	}
	else
	{
		if(m_pState != NULL && m_pState->GetStateType() != STATE_TYPE_ZOMBIE_SKINNY_MALE_RED_WALK1)
		{
			SetState(new CZombie_Skinny_Male_Red_Walk1(2));
			return;
		}
	}
}

void CZombie_Skinny_Male_Red::DropZombieEyeBlue()
{
	Item* pItem = new Item(_T("Á»ºñ´«¾Ë(Ã»)"), _T("Item_Quest_7"), NULL, 0, ITEM_TYPE_QUEST, QUEST_ID_7, -1, -1, 1, 1, 2, 0, 1000, 1, 0, 0);
	CDropItem* pDropItem = new CDropItem(_T("Item"), OBJ_TYPE_DYNAMIC, pItem);
	m_pLayer->AddObject(pDropItem, LAYER_TYPE_DROP);

	CTransformCom* pTransformCom = (CTransformCom*)pDropItem->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = m_pTransformCom->m_vPos;

	pDropItem->Initialize();
}