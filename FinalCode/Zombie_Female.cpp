#include "StdAfx.h"
#include "Zombie_Female.h"

CZombie_Female::CZombie_Female(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, int _iLevel)
: CMonster(_tszObjKey, _eObjType, _iLevel)
{
	// Info
	_tcscpy_s(m_info.tszName, MIN_STR, _T("뒤틀린 어미"));

	// Stat
	m_stat.iLife = m_stat.iMaxLife = _iLevel * 130;
	m_stat.iStrength = _iLevel * 3;

	// CollisionCom
	m_pCollisionCom = new CCollisionCom(COLL_TYPE_MONSTER, new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 60.0f), new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 30.0f));
	m_pCollisionCom->m_CollisionVec.push_back(new Collision(COLLISION_DAMAGE, &m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 50.0f, 0.0f), 20.0f, 50.0f, 20.0f));
	AddComponent(m_pCollisionCom);

	// PathFindCom
	CPathFindCom* pPathFindCom = new CPathFindCom(PATH_TYPE_MONSTER, 80.0f);
	AddComponent(pPathFindCom);

	// BufferCom
	CBufferCom* pBufferCom = new CBufferCom;
	pBufferCom->AddBuffer(_T("Zombie_Female"));
	AddComponent(pBufferCom);

	// LeftHandBone
	CDynamicMesh*	pDynamicMesh = (CDynamicMesh*)pBufferCom->m_BufferVec[0];
	m_LeftHandBone.pFrame = (MeshFrame*)D3DXFrameFind(pDynamicMesh->m_pRootFrame, "left_middle1");
	m_JawBone.pFrame = (MeshFrame*)D3DXFrameFind(pDynamicMesh->m_pRootFrame, "Jaw");
	m_PukeGroundBone.pFrame = (MeshFrame*)D3DXFrameFind(pDynamicMesh->m_pRootFrame, "pukeGround");
}

CZombie_Female::~CZombie_Female()
{
	Release();
}

void CZombie_Female::Initialize()
{
	CMonster::Initialize();
}

int CZombie_Female::Update()
{
	CMonster::Update();

	m_LeftHandBone.mWorld = m_LeftHandBone.pFrame->mCombinedMatrix * m_pTransformCom->m_mWorld;
	m_JawBone.mWorld = m_JawBone.pFrame->mCombinedMatrix * m_pTransformCom->m_mWorld;
	m_PukeGroundBone.mWorld = m_PukeGroundBone.pFrame->mCombinedMatrix * m_pTransformCom->m_mWorld;

	return 0;
}

void CZombie_Female::Render()
{
	CMonster::Render();
}

void CZombie_Female::Release()
{
}

void CZombie_Female::CreateAttack()
{
	if(m_pCollisionCom == NULL)
		return;

	switch(m_pState->GetStateType())
	{
	case STATE_TYPE_ZOMBIE_FEMALE_ATTACK:
		m_pCollisionCom->m_CollisionVec.push_back(new Collision(COLLISION_ATTACK, &m_LeftHandBone.mWorld, &D3DXVECTOR3(0.f, 0.f, 0.f), 20.f, 20.f, 20.f));
		break;
	case STATE_TYPE_ZOMBIE_FEMALE_ATTACK2:
		m_pCollisionCom->m_CollisionVec.push_back(new Collision(COLLISION_ATTACK, &m_LeftHandBone.mWorld, &D3DXVECTOR3(0.f, 0.f, 0.f), 20.f, 20.f, 20.f));
		break;
	case STATE_TYPE_ZOMBIE_FEMALE_ATTACK3:
		break;
	case STATE_TYPE_ZOMBIE_FEMALE_ATTACK4:
		break;
	case STATE_TYPE_ZOMBIE_FEMALE_DEATH:
		break;
	case STATE_TYPE_ZOMBIE_FEMALE_HIT:
		break;
	case STATE_TYPE_ZOMBIE_FEMALE_IDLE:
		break;
	case STATE_TYPE_ZOMBIE_FEMALE_WALK:
		break;
	}

	// CreateAttack
	CMonster::CreateAttack();
}

void CZombie_Female::Damage(CPlayer* _pPlayer)
{
	// PreLife
	int iPreLife = m_stat.iLife;

	// Damage
	CMonster::Damage(_pPlayer);

	// CurLife
	int iCurLife = m_stat.iLife;

	// Death
	if(m_stat.iLife <= 0 && m_pState->GetStateType() != STATE_TYPE_ZOMBIE_FEMALE_DEATH)
	{
		SetState(new CZombie_Female_Death);

		if(rand() % 100 > 90)
			DropZombieEyeRed();

		return;
	}

	// Hit
	if(iCurLife - iPreLife > m_stat.iMaxLife * 0.3f)
	{
		SetState(new CZombie_Female_Hit);
		return;
	}
	else
	{
		if(m_pState != NULL && m_pState->GetStateType() != STATE_TYPE_ZOMBIE_FEMALE_WALK)
		{
			SetState(new CZombie_Female_Walk(3));
			return;
		}
	}
}

void CZombie_Female::Damage(CEffect* _pEffect)
{
	// PreLife
	int iPreLife = m_stat.iLife;

	// Damage
	CMonster::Damage(_pEffect);

	// CurLife
	int iCurLife = m_stat.iLife;

	// Death
	if(m_stat.iLife <= 0 && m_pState->GetStateType() != STATE_TYPE_ZOMBIE_FEMALE_DEATH)
	{
		SetState(new CZombie_Female_Death);

		if(rand() % 100 > 90)
			DropZombieEyeRed();

		return;
	}

	// Hit
	if(iCurLife - iPreLife > m_stat.iMaxLife * 0.3f)
	{
		SetState(new CZombie_Female_Hit);
		return;
	}
	else
	{
		if(m_pState != NULL && m_pState->GetStateType() != STATE_TYPE_ZOMBIE_FEMALE_WALK)
		{
			SetState(new CZombie_Female_Walk(3));
			return;
		}
	}
}

void CZombie_Female::DropZombieEyeRed()
{
	Item* pItem = new Item(_T("좀비눈알(적)"), _T("Item_Quest_8"), NULL, 0, ITEM_TYPE_QUEST, QUEST_ID_8, -1, -1, 1, 1, 2, 0, 2000, 1, 0, 0);
	CDropItem* pDropItem = new CDropItem(_T("Item"), OBJ_TYPE_DYNAMIC, pItem);
	m_pLayer->AddObject(pDropItem, LAYER_TYPE_DROP);

	CTransformCom* pTransformCom = (CTransformCom*)pDropItem->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = m_pTransformCom->m_vPos;

	pDropItem->Initialize();
}