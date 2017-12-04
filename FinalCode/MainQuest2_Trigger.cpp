#include "StdAfx.h"
#include "MainQuest2_Trigger.h"

CMainQuest2_Trigger::CMainQuest2_Trigger(TCHAR* _tszObjKey, OBJ_TYPE _eObjType)
: CTrigger(_tszObjKey, _eObjType)
{
	// Mode
	m_iMode = 0;

	// Time
	m_fTime = 0.0f;
}

CMainQuest2_Trigger::~CMainQuest2_Trigger()
{
	Release();
}

void CMainQuest2_Trigger::Initialize()
{
	CTrigger::Initialize();
}

int CMainQuest2_Trigger::Update()
{
	CTrigger::Update();

	switch(m_iMode)
	{
	case 0:
		Mode0();
		break;

	case 1:
		Mode1();
		break;

	case 2:
		Mode2();
		break;

	case 3:
		Mode3();
		break;

	case 4:
		Mode4();
		break;

	case 5:
		Mode5();
		break;
	}

	return 0;
}

void CMainQuest2_Trigger::Render()
{
	CTrigger::Render();
}

void CMainQuest2_Trigger::Release()
{
}

void CMainQuest2_Trigger::Mode0()
{
	// TransformCom
	CTransformCom* pTransformCom;

	// Zombie_Skinny_Male_White0
	CZombie_Skinny_Male_White* pZombie_Skinny_Male_White0 = new CZombie_Skinny_Male_White(_T("Monster"), OBJ_TYPE_DYNAMIC, 1);
	m_pLayer->AddObject(pZombie_Skinny_Male_White0, LAYER_TYPE_MONSTER);
	pTransformCom = (CTransformCom*)pZombie_Skinny_Male_White0->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(D3DXVECTOR3(8712.0f, 318.0f, 5594.0f));
	pZombie_Skinny_Male_White0->Initialize();
	pZombie_Skinny_Male_White0->SetState(new CZombie_Skinny_Male_White_Spawn);
	m_MonsterVec.push_back(pZombie_Skinny_Male_White0);

	// Zombie_Skinny_Male_White1
	CZombie_Skinny_Male_White* pZombie_Skinny_Male_White1 = new CZombie_Skinny_Male_White(_T("Monster"), OBJ_TYPE_DYNAMIC, 1);
	m_pLayer->AddObject(pZombie_Skinny_Male_White1, LAYER_TYPE_MONSTER);
	pTransformCom = (CTransformCom*)pZombie_Skinny_Male_White1->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(D3DXVECTOR3(8774.0f, 314.0f, 5761.0f));
	pZombie_Skinny_Male_White1->Initialize();
	pZombie_Skinny_Male_White1->SetState(new CZombie_Skinny_Male_White_Spawn);
	m_MonsterVec.push_back(pZombie_Skinny_Male_White1);

	// Zombie_Skinny_Male_White2
	CZombie_Skinny_Male_White* pZombie_Skinny_Male_White2 = new CZombie_Skinny_Male_White(_T("Monster"), OBJ_TYPE_DYNAMIC, 1);
	m_pLayer->AddObject(pZombie_Skinny_Male_White2, LAYER_TYPE_MONSTER);
	pTransformCom = (CTransformCom*)pZombie_Skinny_Male_White2->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(D3DXVECTOR3(8748.0f, 312.0f, 5938.0f));
	pZombie_Skinny_Male_White2->Initialize();
	pZombie_Skinny_Male_White2->SetState(new CZombie_Skinny_Male_White_Spawn);
	m_MonsterVec.push_back(pZombie_Skinny_Male_White2);

	// Zombie_Skinny_Male_White3
	CZombie_Skinny_Male_White* pZombie_Skinny_Male_White3 = new CZombie_Skinny_Male_White(_T("Monster"), OBJ_TYPE_DYNAMIC, 1);
	m_pLayer->AddObject(pZombie_Skinny_Male_White3, LAYER_TYPE_MONSTER);
	pTransformCom = (CTransformCom*)pZombie_Skinny_Male_White3->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(D3DXVECTOR3(8617.0f, 310.0f, 6072.0f));
	pZombie_Skinny_Male_White3->Initialize();
	pZombie_Skinny_Male_White3->SetState(new CZombie_Skinny_Male_White_Spawn);
	m_MonsterVec.push_back(pZombie_Skinny_Male_White3);
	
	++m_iMode;
}

void CMainQuest2_Trigger::Mode1()
{
	for(size_t i = 0; i < m_MonsterVec.size(); ++i)
	{
		if(m_MonsterVec[i]->IsDestroy() == true)
		{
			for(size_t j = i + 1; j < m_MonsterVec.size(); ++j)
				m_MonsterVec[j - 1] = m_MonsterVec[j];

			m_MonsterVec.pop_back();
			--i;
		}
	}

	if(m_MonsterVec.size() == 0)
		++m_iMode;
}

void CMainQuest2_Trigger::Mode2()
{
	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();
	if(m_fTime > 3.0f)
	{
		m_fTime = 0.0f;
		++m_iMode;
	}
}

void CMainQuest2_Trigger::Mode3()
{
	// TransformCom
	CTransformCom* pTransformCom;

	// Zombie_Male0
	CZombie_Male* pZombie_Male0 = new CZombie_Male(_T("Monster"), OBJ_TYPE_DYNAMIC, 2);
	m_pLayer->AddObject(pZombie_Male0, LAYER_TYPE_MONSTER);
	pTransformCom = (CTransformCom*)pZombie_Male0->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(D3DXVECTOR3(8731.0f, 312.0f, 5951.0f));
	pZombie_Male0->Initialize();
	pZombie_Male0->SetState(new CZombie_Male_Idle(0));
	m_MonsterVec.push_back(pZombie_Male0);

	// Zombie_Male1
	CZombie_Male* pZombie_Male1 = new CZombie_Male(_T("Monster"), OBJ_TYPE_DYNAMIC, 2);
	m_pLayer->AddObject(pZombie_Male1, LAYER_TYPE_MONSTER);
	pTransformCom = (CTransformCom*)pZombie_Male1->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(D3DXVECTOR3(8792.0f, 317.0f, 5775.0f));
	pZombie_Male1->Initialize();
	pZombie_Male1->SetState(new CZombie_Male_Idle(0));
	m_MonsterVec.push_back(pZombie_Male1);

	// Zombie_Male2
	CZombie_Male* pZombie_Male2 = new CZombie_Male(_T("Monster"), OBJ_TYPE_DYNAMIC, 2);
	m_pLayer->AddObject(pZombie_Male2, LAYER_TYPE_MONSTER);
	pTransformCom = (CTransformCom*)pZombie_Male2->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(D3DXVECTOR3(8697.0f, 315.0f, 5619.0f));
	pZombie_Male2->Initialize();
	pZombie_Male2->SetState(new CZombie_Male_Idle(0));
	m_MonsterVec.push_back(pZombie_Male2);

	++m_iMode;
}

void CMainQuest2_Trigger::Mode4()
{
	for(size_t i = 0; i < m_MonsterVec.size(); ++i)
	{
		if(m_MonsterVec[i]->IsDestroy() == true)
		{
			for(size_t j = i + 1; j < m_MonsterVec.size(); ++j)
				m_MonsterVec[j - 1] = m_MonsterVec[j];

			m_MonsterVec.pop_back();
			--i;
		}
	}

	if(m_MonsterVec.size() == 0)
		++m_iMode;
}

void CMainQuest2_Trigger::Mode5()
{
	// NPCVec
	vector<CObject*> NPCVec;
	m_pLayer->FindObjects(NPCVec, _T("NPC"), LAYER_TYPE_NPC);

	for(size_t i = 0; i < NPCVec.size(); ++i)
	{
		CNPC* pNPC = (CNPC*)NPCVec[i];
		if(pNPC->GetNPCType() == NPC_TYPE_TRISTRAM_GUARD)
		{
			pNPC->SetMode(2);
			break;
		}
	}

	Destroy();
}