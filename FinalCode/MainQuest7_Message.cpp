#include "StdAfx.h"
#include "MainQuest7_Message.h"

CMainQuest7_Message::CMainQuest7_Message(TCHAR* _tszObjKey, OBJ_TYPE _eObjType)
: CQuestMessage(_tszObjKey, _eObjType)
{
	// Mode
	m_iMode = 0;

	// Name
	_tcscpy_s(m_tszName, MIN_STR, _T("타스한"));

	// Text
	_tcscpy_s(m_tszText, MAX_STR, _T("쇠조각은 구해왔는가!?"));
}

CMainQuest7_Message::~CMainQuest7_Message()
{
	Release();
}

void CMainQuest7_Message::Initialize()
{
	CQuestMessage::Initialize();

	// TransformCom
	CTransformCom* pTransformCom;

	// PortraitSign
	m_pPortraitSign = new CPortraitSign(NULL, OBJ_TYPE_STATIC, _T("Sign_Tashun"));
	m_pLayer->AddObject(m_pPortraitSign, LAYER_TYPE_UI);

	pTransformCom = (CTransformCom*)m_pPortraitSign->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(-0.305f, -0.592f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.118006f, 0.187f, 0.0f);

	m_pPortraitSign->Initialize();
}

int CMainQuest7_Message::Update()
{
	CQuestMessage::Update();

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
	}

	return 0;
}

void CMainQuest7_Message::Render()
{
	CQuestMessage::Render();
}

void CMainQuest7_Message::Release()
{
}

void CMainQuest7_Message::Mode0()
{
	if(m_pXButton->IsLUp())
	{
		// FindIndexVec
		vector<int> FindIndexVec;
		CItemMgr::GetInstance()->FindItemInInven(FindIndexVec, &Item(_T("쇠조각"), _T("Item_Materials_1"), NULL, 0, ITEM_TYPE_MATERIAL, MATERIAL_ID_IRON, -1, -1, 1, 1, 2, 0, 1000, 1, 0, 0));

		int iCnt = 0;
		for(size_t i = 0; i < FindIndexVec.size(); ++i)
			iCnt += CItemMgr::GetInstance()->GetItemInInven(FindIndexVec[i])->iNum;

		if(iCnt >= 10)
		{
			_tcscpy_s(m_tszText, MIN_STR, _T("허허.. 제대로 구해왔구만. 고맙네~"));
			m_iMode = 2;
		}
		else
		{
			_tcscpy_s(m_tszText, MIN_STR, _T("쇠조각이 없지 않은가? 서두르게.."));
			m_iMode = 1;
		}
	}
}

void CMainQuest7_Message::Mode1()
{
	if(m_pXButton->IsLUp())
		Destroy();
}

void CMainQuest7_Message::Mode2()
{
	if(m_pXButton->IsLUp())
	{
		_tcscpy_s(m_tszText, MIN_STR, _T("부탁하는 김에 장비로 만들어서 와주면 안되겠나..? 지금 화장실\n이 급해서 말이야.."));
		m_iMode = 3;
	}
}

void CMainQuest7_Message::Mode3()
{
	if(m_pXButton->IsLUp())
	{
		// QuestAlarmMessage
		CQuestAlarmMessage* pQuestAlarmMessage = new CQuestAlarmMessage(NULL, OBJ_TYPE_DYNAMIC, _T("메인퀘스트7 : 아이템 제련"));
		m_pLayer->AddObject(pQuestAlarmMessage, LAYER_TYPE_UI);
		pQuestAlarmMessage->Initialize();

		// AddAchieve
		CQuestMgr::GetInstance()->AddAchieve(new Achieve(ACHIEVE_TYPE_MAIN_QUEST7));

		// Quest
		Quest* pQuest = CQuestMgr::GetInstance()->GetQuest(QUEST_TYPE_MAIN);
		pQuest->iStep = 7;

		// NPCVec
		vector<CObject*> NPCVec;
		m_pLayer->FindObjects(NPCVec, _T("NPC"), LAYER_TYPE_NPC);

		for(size_t i = 0; i < NPCVec.size(); ++i)
		{
			CNPC* pNPC = (CNPC*)NPCVec[i];
			if(pNPC->GetNPCType() == NPC_TYPE_TRISTRAM_TASHUN)
			{
				pNPC->SetMode(6);
				break;
			}
		}

		Destroy();
	}
}