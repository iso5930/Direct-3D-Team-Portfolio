#include "StdAfx.h"
#include "MonsterSpawnTrigger.h"

CMonsterSpawnTrigger::CMonsterSpawnTrigger(TCHAR* _tszObjKey, OBJ_TYPE _eObjType)
: CTrigger(_tszObjKey, _eObjType)
{
	// Mode
	m_iMode = 0;

	// Time
	m_fTime = 0.0f;
}

CMonsterSpawnTrigger::~CMonsterSpawnTrigger()
{
	Release();
}

void CMonsterSpawnTrigger::Initialize()
{
	CTrigger::Initialize();
}

int CMonsterSpawnTrigger::Update()
{
	CTrigger::Update();

	for(size_t i = 0; i < m_MonsterVec.size(); ++i)
	{
		if(m_MonsterVec[i] == NULL)
			continue;

		if(m_MonsterVec[i]->IsDestroy() == true)
			m_MonsterVec[i] = NULL;
	}

	for(size_t i = 0; i < m_MonsterVec.size(); ++i)
	{
		if(m_MonsterVec[i] == NULL)
		{
			m_TimeVec[i] += CTimeMgr::GetInstance()->GetDeltaTime();
			if(m_TimeVec[i] > 30.0f)
			{
				m_TimeVec[i] = 0.0f;
				m_MonsterVec[i] = CreateMonster(m_MonsterSpawnVec[i]);
			}
		}
	}

	return 0;
}

void CMonsterSpawnTrigger::Render()
{
	CTrigger::Render();
}

void CMonsterSpawnTrigger::Release()
{
	for(size_t i = 0; i < m_MonsterSpawnVec.size(); ++i)
	{
		delete m_MonsterSpawnVec[i];
		m_MonsterSpawnVec[i] = NULL;
	}
	m_MonsterSpawnVec.clear();
}

void CMonsterSpawnTrigger::AddMonsterSpawn(MonsterSpawn* _pMonsterSpawn)
{
	m_MonsterSpawnVec.push_back(_pMonsterSpawn);
	m_MonsterVec.push_back(CreateMonster(_pMonsterSpawn));
	m_TimeVec.push_back(0.0f);
}

CMonster* CMonsterSpawnTrigger::CreateMonster(MonsterSpawn* _pMonsterSpawn)
{
	CMonster* pMonster = NULL;

	if(_pMonsterSpawn->eMonsterType == MONSTER_TYPE_BUTCHER)
	{
		pMonster = new CButcher(_T("Monster"), OBJ_TYPE_DYNAMIC, _pMonsterSpawn->iLevel);
		m_pLayer->AddObject(pMonster, LAYER_TYPE_MONSTER);

		CTransformCom* pTransformCom = (CTransformCom*)pMonster->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = _pMonsterSpawn->vPos;
		pTransformCom->m_vAngle = _pMonsterSpawn->vAngle;
		pTransformCom->m_vSize = _pMonsterSpawn->vSize;

		pMonster->Initialize();
		pMonster->SetState(new CButcher_Idle);
	}
	else if(_pMonsterSpawn->eMonsterType == MONSTER_TYPE_GHOUL)
	{
		pMonster = new CGhoul(_T("Monster"), OBJ_TYPE_DYNAMIC, _pMonsterSpawn->iLevel);
		m_pLayer->AddObject(pMonster, LAYER_TYPE_MONSTER);

		CTransformCom* pTransformCom = (CTransformCom*)pMonster->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = _pMonsterSpawn->vPos;
		pTransformCom->m_vAngle = _pMonsterSpawn->vAngle;
		pTransformCom->m_vSize = _pMonsterSpawn->vSize;

		pMonster->Initialize();
		pMonster->SetState(new CGhoul_Idle);
	}
	else if(_pMonsterSpawn->eMonsterType == MONSTER_TYPE_SKELETON_ARCHER_BROWN)
	{
		pMonster = new CSkeleton_Archer_Brown(_T("Monster"), OBJ_TYPE_DYNAMIC, _pMonsterSpawn->iLevel);
		m_pLayer->AddObject(pMonster, LAYER_TYPE_MONSTER);

		CTransformCom* pTransformCom = (CTransformCom*)pMonster->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = _pMonsterSpawn->vPos;
		pTransformCom->m_vAngle = _pMonsterSpawn->vAngle;
		pTransformCom->m_vSize = _pMonsterSpawn->vSize;

		pMonster->Initialize();
		pMonster->SetState(new CSkeleton_Archer_Brown_Spawn);
	}
	else if(_pMonsterSpawn->eMonsterType == MONSTER_TYPE_SKELETON_ARCHER_MINT)
	{
		pMonster = new CSkeleton_Archer_Mint(_T("Monster"), OBJ_TYPE_DYNAMIC, _pMonsterSpawn->iLevel);
		m_pLayer->AddObject(pMonster, LAYER_TYPE_MONSTER);

		CTransformCom* pTransformCom = (CTransformCom*)pMonster->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = _pMonsterSpawn->vPos;
		pTransformCom->m_vAngle = _pMonsterSpawn->vAngle;
		pTransformCom->m_vSize = _pMonsterSpawn->vSize;

		pMonster->Initialize();
		pMonster->SetState(new CSkeleton_Archer_Mint_Spawn);
	}
	else if(_pMonsterSpawn->eMonsterType == MONSTER_TYPE_SKELETON_ARCHER_RED)
	{
		pMonster = new CSkeleton_Archer_Red(_T("Monster"), OBJ_TYPE_DYNAMIC, _pMonsterSpawn->iLevel);
		m_pLayer->AddObject(pMonster, LAYER_TYPE_MONSTER);

		CTransformCom* pTransformCom = (CTransformCom*)pMonster->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = _pMonsterSpawn->vPos;
		pTransformCom->m_vAngle = _pMonsterSpawn->vAngle;
		pTransformCom->m_vSize = _pMonsterSpawn->vSize;

		pMonster->Initialize();
		pMonster->SetState(new CSkeleton_Archer_Red_Spawn);
	}
	else if(_pMonsterSpawn->eMonsterType == MONSTER_TYPE_SKELETON_AXE_BLUE)
	{
		pMonster = new CSkeleton_Axe_Blue(_T("Monster"), OBJ_TYPE_DYNAMIC, _pMonsterSpawn->iLevel);
		m_pLayer->AddObject(pMonster, LAYER_TYPE_MONSTER);

		CTransformCom* pTransformCom = (CTransformCom*)pMonster->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = _pMonsterSpawn->vPos;
		pTransformCom->m_vAngle = _pMonsterSpawn->vAngle;
		pTransformCom->m_vSize = _pMonsterSpawn->vSize;

		pMonster->Initialize();
		pMonster->SetState(new CSkeleton_Axe_Blue_Spawn);
	}
	else if(_pMonsterSpawn->eMonsterType == MONSTER_TYPE_SKELETON_AXE_RED)
	{
		pMonster = new CSkeleton_Axe_Red(_T("Monster"), OBJ_TYPE_DYNAMIC, _pMonsterSpawn->iLevel);
		m_pLayer->AddObject(pMonster, LAYER_TYPE_MONSTER);

		CTransformCom* pTransformCom = (CTransformCom*)pMonster->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = _pMonsterSpawn->vPos;
		pTransformCom->m_vAngle = _pMonsterSpawn->vAngle;
		pTransformCom->m_vSize = _pMonsterSpawn->vSize;

		pMonster->Initialize();
		pMonster->SetState(new CSkeleton_Axe_Red_Spawn);
	}
	else if(_pMonsterSpawn->eMonsterType == MONSTER_TYPE_SKELETON_KING)
	{
		pMonster = new CSkeleton_King(_T("Monster"), OBJ_TYPE_DYNAMIC, _pMonsterSpawn->iLevel);
		m_pLayer->AddObject(pMonster, LAYER_TYPE_MONSTER);

		CTransformCom* pTransformCom = (CTransformCom*)pMonster->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = _pMonsterSpawn->vPos;
		pTransformCom->m_vAngle = _pMonsterSpawn->vAngle;
		pTransformCom->m_vSize = _pMonsterSpawn->vSize;

		pMonster->Initialize();
		pMonster->SetState(new CSkeleton_King_Intro_Idle);
	}
	else if(_pMonsterSpawn->eMonsterType == MONSTER_TYPE_SKELETON_ONEHAND_BLUE)
	{
		pMonster = new CSkeleton_OneHand_Blue(_T("Monster"), OBJ_TYPE_DYNAMIC, _pMonsterSpawn->iLevel);
		m_pLayer->AddObject(pMonster, LAYER_TYPE_MONSTER);

		CTransformCom* pTransformCom = (CTransformCom*)pMonster->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = _pMonsterSpawn->vPos;
		pTransformCom->m_vAngle = _pMonsterSpawn->vAngle;
		pTransformCom->m_vSize = _pMonsterSpawn->vSize;

		pMonster->Initialize();
		pMonster->SetState(new CSkeleton_OneHand_Blue_Spawn);
	}
	else if(_pMonsterSpawn->eMonsterType == MONSTER_TYPE_SKELETON_ONEHAND_BROWN)
	{
		pMonster = new CSkeleton_OneHand_Brown(_T("Monster"), OBJ_TYPE_DYNAMIC, _pMonsterSpawn->iLevel);
		m_pLayer->AddObject(pMonster, LAYER_TYPE_MONSTER);

		CTransformCom* pTransformCom = (CTransformCom*)pMonster->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = _pMonsterSpawn->vPos;
		pTransformCom->m_vAngle = _pMonsterSpawn->vAngle;
		pTransformCom->m_vSize = _pMonsterSpawn->vSize;

		pMonster->Initialize();
		pMonster->SetState(new CSkeleton_OneHand_Brown_Spawn);
	}
	else if(_pMonsterSpawn->eMonsterType == MONSTER_TYPE_SKELETON_ONEHAND_MINT)
	{
		pMonster = new CSkeleton_OneHand_Mint(_T("Monster"), OBJ_TYPE_DYNAMIC, _pMonsterSpawn->iLevel);
		m_pLayer->AddObject(pMonster, LAYER_TYPE_MONSTER);

		CTransformCom* pTransformCom = (CTransformCom*)pMonster->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = _pMonsterSpawn->vPos;
		pTransformCom->m_vAngle = _pMonsterSpawn->vAngle;
		pTransformCom->m_vSize = _pMonsterSpawn->vSize;

		pMonster->Initialize();
		pMonster->SetState(new CSkeleton_OneHand_Mint_Spawn);
	}
	else if(_pMonsterSpawn->eMonsterType == MONSTER_TYPE_SKELETON_SHIELD_BLUE)
	{
		pMonster = new CSkeleton_Shield_Blue(_T("Monster"), OBJ_TYPE_DYNAMIC, _pMonsterSpawn->iLevel);
		m_pLayer->AddObject(pMonster, LAYER_TYPE_MONSTER);
		
		CTransformCom* pTransformCom = (CTransformCom*)pMonster->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = _pMonsterSpawn->vPos;
		pTransformCom->m_vAngle = _pMonsterSpawn->vAngle;
		pTransformCom->m_vSize = _pMonsterSpawn->vSize;

		pMonster->Initialize();
		pMonster->SetState(new CSkeleton_Shield_Blue_Spawn);
	}
	else if(_pMonsterSpawn->eMonsterType == MONSTER_TYPE_SKELETON_SHIELD_BROWN)
	{
		pMonster = new CSkeleton_Shield_Brown(_T("Monster"), OBJ_TYPE_DYNAMIC, _pMonsterSpawn->iLevel);
		m_pLayer->AddObject(pMonster, LAYER_TYPE_MONSTER);

		CTransformCom* pTransformCom = (CTransformCom*)pMonster->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = _pMonsterSpawn->vPos;
		pTransformCom->m_vAngle = _pMonsterSpawn->vAngle;
		pTransformCom->m_vSize = _pMonsterSpawn->vSize;

		pMonster->Initialize();
		pMonster->SetState(new CSkeleton_Shield_Brown_Spawn);
	}
	else if(_pMonsterSpawn->eMonsterType == MONSTER_TYPE_SKELETON_SHIELD_MINT)
	{
		pMonster = new CSkeleton_Shield_Mint(_T("Monster"), OBJ_TYPE_DYNAMIC, _pMonsterSpawn->iLevel);
		m_pLayer->AddObject(pMonster, LAYER_TYPE_MONSTER);

		CTransformCom* pTransformCom = (CTransformCom*)pMonster->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = _pMonsterSpawn->vPos;
		pTransformCom->m_vAngle = _pMonsterSpawn->vAngle;
		pTransformCom->m_vSize = _pMonsterSpawn->vSize;

		pMonster->Initialize();
		pMonster->SetState(new CSkeleton_Shield_Mint_Spawn);
	}
	else if(_pMonsterSpawn->eMonsterType == MONSTER_TYPE_SKELETON_SHIELD_RED)
	{
		pMonster = new CSkeleton_Shield_Red(_T("Monster"), OBJ_TYPE_DYNAMIC, _pMonsterSpawn->iLevel);
		m_pLayer->AddObject(pMonster, LAYER_TYPE_MONSTER);

		CTransformCom* pTransformCom = (CTransformCom*)pMonster->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = _pMonsterSpawn->vPos;
		pTransformCom->m_vAngle = _pMonsterSpawn->vAngle;
		pTransformCom->m_vSize = _pMonsterSpawn->vSize;

		pMonster->Initialize();
		pMonster->SetState(new CSkeleton_Shield_Red_Spawn);
	}
	else if(_pMonsterSpawn->eMonsterType == MONSTER_TYPE_SKELETON_SUMMONER_BLUE)
	{
		pMonster = new CSkeleton_Summoner_Blue(_T("Monster"), OBJ_TYPE_DYNAMIC, _pMonsterSpawn->iLevel);
		m_pLayer->AddObject(pMonster, LAYER_TYPE_MONSTER);

		CTransformCom* pTransformCom = (CTransformCom*)pMonster->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = _pMonsterSpawn->vPos;
		pTransformCom->m_vAngle = _pMonsterSpawn->vAngle;
		pTransformCom->m_vSize = _pMonsterSpawn->vSize;

		pMonster->Initialize();
		pMonster->SetState(new CSkeleton_Summoner_Blue_Idle(0));
	}
	else if(_pMonsterSpawn->eMonsterType == MONSTER_TYPE_SKELETON_SUMMONER_BROWN)
	{
		pMonster = new CSkeleton_Summoner_Brown(_T("Monster"), OBJ_TYPE_DYNAMIC, _pMonsterSpawn->iLevel);
		m_pLayer->AddObject(pMonster, LAYER_TYPE_MONSTER);

		CTransformCom* pTransformCom = (CTransformCom*)pMonster->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = _pMonsterSpawn->vPos;
		pTransformCom->m_vAngle = _pMonsterSpawn->vAngle;
		pTransformCom->m_vSize = _pMonsterSpawn->vSize;

		pMonster->Initialize();
		pMonster->SetState(new CSkeleton_Summoner_Brown_Idle(0));
	}
	else if(_pMonsterSpawn->eMonsterType == MONSTER_TYPE_SKELETON_SUMMONER_RED)
	{
		pMonster = new CSkeleton_Summoner_Red(_T("Monster"), OBJ_TYPE_DYNAMIC, _pMonsterSpawn->iLevel);
		m_pLayer->AddObject(pMonster, LAYER_TYPE_MONSTER);

		CTransformCom* pTransformCom = (CTransformCom*)pMonster->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = _pMonsterSpawn->vPos;
		pTransformCom->m_vAngle = _pMonsterSpawn->vAngle;
		pTransformCom->m_vSize = _pMonsterSpawn->vSize;

		pMonster->Initialize();
		pMonster->SetState(new CSkeleton_Summoner_Red_Idle(0));
	}
	else if(_pMonsterSpawn->eMonsterType == MONSTER_TYPE_STITCH)
	{
		pMonster = new CStitch(_T("Monster"), OBJ_TYPE_DYNAMIC, _pMonsterSpawn->iLevel);
		m_pLayer->AddObject(pMonster, LAYER_TYPE_MONSTER);

		CTransformCom* pTransformCom = (CTransformCom*)pMonster->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = _pMonsterSpawn->vPos;
		pTransformCom->m_vAngle = _pMonsterSpawn->vAngle;
		pTransformCom->m_vSize = _pMonsterSpawn->vSize;

		pMonster->Initialize();
		pMonster->SetState(new CStitch_Idle);
	}
	else if(_pMonsterSpawn->eMonsterType == MONSTER_TYPE_TRIUNE_BERSERKER)
	{
		pMonster = new CTriune_Berserker(_T("Monster"), OBJ_TYPE_DYNAMIC, _pMonsterSpawn->iLevel);
		m_pLayer->AddObject(pMonster, LAYER_TYPE_MONSTER);

		CTransformCom* pTransformCom = (CTransformCom*)pMonster->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = _pMonsterSpawn->vPos;
		pTransformCom->m_vAngle = _pMonsterSpawn->vAngle;
		pTransformCom->m_vSize = _pMonsterSpawn->vSize;

		pMonster->Initialize();
		pMonster->SetState(new CTriune_Berserker_Idle);
	}
	else if(_pMonsterSpawn->eMonsterType == MONSTER_TYPE_TRIUNE_CULTISTS)
	{
		pMonster = new CTriune_Cultists(_T("Monster"), OBJ_TYPE_DYNAMIC, _pMonsterSpawn->iLevel);
		m_pLayer->AddObject(pMonster, LAYER_TYPE_MONSTER);

		CTransformCom* pTransformCom = (CTransformCom*)pMonster->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = _pMonsterSpawn->vPos;
		pTransformCom->m_vAngle = _pMonsterSpawn->vAngle;
		pTransformCom->m_vSize = _pMonsterSpawn->vSize;

		pMonster->Initialize();
		pMonster->SetState(new CTriune_Cultists_Idle);
	}
	else if(_pMonsterSpawn->eMonsterType == MONSTER_TYPE_TRIUNE_POSSESSED)
	{
		pMonster = new CTriune_Possessed(_T("Monster"), OBJ_TYPE_DYNAMIC, _pMonsterSpawn->iLevel);
		m_pLayer->AddObject(pMonster, LAYER_TYPE_MONSTER);

		CTransformCom* pTransformCom = (CTransformCom*)pMonster->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = _pMonsterSpawn->vPos;
		pTransformCom->m_vAngle = _pMonsterSpawn->vAngle;
		pTransformCom->m_vSize = _pMonsterSpawn->vSize;

		pMonster->Initialize();
		pMonster->SetState(new CTriune_Possessed_Idle(0));
	}
	else if(_pMonsterSpawn->eMonsterType == MONSTER_TYPE_TRIUNE_VESSEL)
	{
		pMonster = new CTriune_Vessel(_T("Monster"), OBJ_TYPE_DYNAMIC, _pMonsterSpawn->iLevel);
		m_pLayer->AddObject(pMonster, LAYER_TYPE_MONSTER);

		CTransformCom* pTransformCom = (CTransformCom*)pMonster->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = _pMonsterSpawn->vPos;
		pTransformCom->m_vAngle = _pMonsterSpawn->vAngle;
		pTransformCom->m_vSize = _pMonsterSpawn->vSize;

		pMonster->Initialize();
		pMonster->SetState(new CTriune_Vessel_Idle);
	}
	else if(_pMonsterSpawn->eMonsterType == MONSTER_TYPE_WARDEN)
	{
		pMonster = new CWarden(_T("Monster"), OBJ_TYPE_DYNAMIC, _pMonsterSpawn->iLevel);
		m_pLayer->AddObject(pMonster, LAYER_TYPE_MONSTER);

		CTransformCom* pTransformCom = (CTransformCom*)pMonster->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = _pMonsterSpawn->vPos;
		pTransformCom->m_vAngle = _pMonsterSpawn->vAngle;
		pTransformCom->m_vSize = _pMonsterSpawn->vSize;

		pMonster->Initialize();
		pMonster->SetState(new CWarden_Idle(0));
	}
	else if(_pMonsterSpawn->eMonsterType == MONSTER_TYPE_ZOMBIE_FEMALE)
	{
		pMonster = new CZombie_Female(_T("Monster"), OBJ_TYPE_DYNAMIC, _pMonsterSpawn->iLevel);
		m_pLayer->AddObject(pMonster, LAYER_TYPE_MONSTER);

		CTransformCom* pTransformCom = (CTransformCom*)pMonster->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = _pMonsterSpawn->vPos;
		pTransformCom->m_vAngle = _pMonsterSpawn->vAngle;
		pTransformCom->m_vSize = _pMonsterSpawn->vSize;

		pMonster->Initialize();
		pMonster->SetState(new CZombie_Female_Idle(0));
	}
	else if(_pMonsterSpawn->eMonsterType == MONSTER_TYPE_ZOMBIE_MALE)
	{
		pMonster = new CZombie_Male(_T("Monster"), OBJ_TYPE_DYNAMIC, _pMonsterSpawn->iLevel);
		m_pLayer->AddObject(pMonster, LAYER_TYPE_MONSTER);

		CTransformCom* pTransformCom = (CTransformCom*)pMonster->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = _pMonsterSpawn->vPos;
		pTransformCom->m_vAngle = _pMonsterSpawn->vAngle;
		pTransformCom->m_vSize = _pMonsterSpawn->vSize;

		pMonster->Initialize();
		pMonster->SetState(new CZombie_Male_Idle(0));
	}
	else if(_pMonsterSpawn->eMonsterType == MONSTER_TYPE_ZOMBIE_SKINNY_MALE_RED)
	{
		pMonster = new CZombie_Skinny_Male_Red(_T("Monster"), OBJ_TYPE_DYNAMIC, _pMonsterSpawn->iLevel);
		m_pLayer->AddObject(pMonster, LAYER_TYPE_MONSTER);

		CTransformCom* pTransformCom = (CTransformCom*)pMonster->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = _pMonsterSpawn->vPos;
		pTransformCom->m_vAngle = _pMonsterSpawn->vAngle;
		pTransformCom->m_vSize = _pMonsterSpawn->vSize;

		pMonster->Initialize();
		pMonster->SetState(new CZombie_Skinny_Male_Red_Spawn);
	}
	else if(_pMonsterSpawn->eMonsterType == MONSTER_TYPE_ZOMBIE_SKINNY_MALE_WHITE)
	{
		pMonster = new CZombie_Skinny_Male_White(_T("Monster"), OBJ_TYPE_DYNAMIC, _pMonsterSpawn->iLevel);
		m_pLayer->AddObject(pMonster, LAYER_TYPE_MONSTER);

		CTransformCom* pTransformCom = (CTransformCom*)pMonster->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = _pMonsterSpawn->vPos;
		pTransformCom->m_vAngle = _pMonsterSpawn->vAngle;
		pTransformCom->m_vSize = _pMonsterSpawn->vSize;

		pMonster->Initialize();
		pMonster->SetState(new CZombie_Skinny_Male_White_Spawn);
	}
	
	return pMonster;
}