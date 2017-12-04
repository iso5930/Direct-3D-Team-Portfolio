#include "StdAfx.h"
#include "MainQuest5_Message.h"

CMainQuest5_Message::CMainQuest5_Message(TCHAR* _tszObjKey, OBJ_TYPE _eObjType)
: CQuestMessage(_tszObjKey, _eObjType)
{
	// Mode
	m_iMode = 0;

	// Name
	_tcscpy_s(m_tszName, MIN_STR, _T("타스한"));

	// Text
	_tcscpy_s(m_tszText, MAX_STR, _T("좀비눈알은 가지고 왔는가?"));
}

CMainQuest5_Message::~CMainQuest5_Message()
{
	Release();
}

void CMainQuest5_Message::Initialize()
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

int CMainQuest5_Message::Update()
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
	}

	return 0;
}

void CMainQuest5_Message::Render()
{
	CQuestMessage::Render();
}

void CMainQuest5_Message::Release()
{
}

void CMainQuest5_Message::Mode0()
{
	if(m_pXButton->IsLUp())
	{
		// FindIndexVec1
		vector<int> FindIndexVec1;
		CItemMgr::GetInstance()->FindItemInInven(FindIndexVec1, &Item(_T("좀비눈알(적)"), _T("Item_Quest_8"), NULL, 0, ITEM_TYPE_QUEST, QUEST_ID_8, -1, -1, 1, 1, 2, 0, 1000, 1, 0, 0));

		// FindIndexVec2
		vector<int> FindIndexVec2;
		CItemMgr::GetInstance()->FindItemInInven(FindIndexVec2, &Item(_T("좀비눈알(청)"), _T("Item_Quest_7"), NULL, 0, ITEM_TYPE_QUEST, QUEST_ID_7, -1, -1, 1, 1, 2, 0, 1000, 1, 0, 0));

		if(FindIndexVec1.size() == 0 || FindIndexVec2.size() == 0)
		{
			_tcscpy_s(m_tszText, MAX_STR, _T("좀비눈알이 없지 않은가? 어서 구해오시게!"));
			m_iMode = 1;
		}
		else
		{
			_tcscpy_s(m_tszText, MAX_STR, _T("잘 구해 오셨구만. 수고했네! 자네 덕분에 꽤 오랫동안은 마을이\n평화롭겠어..."));
			m_iMode = 2;
		}
	}
}

void CMainQuest5_Message::Mode1()
{
	if(m_pXButton->IsLUp())
		Destroy();
}

void CMainQuest5_Message::Mode2()
{
	if(m_pXButton->IsLUp())
	{
		// FindIndexVec1
		vector<int> FindIndexVec1;
		CItemMgr::GetInstance()->FindItemInInven(FindIndexVec1, &Item(_T("좀비눈알(적)"), _T("Item_Quest_8"), NULL, 0, ITEM_TYPE_QUEST, QUEST_ID_8, -1, -1, 1, 1, 2, 0, 1000, 1, 0, 0));

		// FindIndexVec2
		vector<int> FindIndexVec2;
		CItemMgr::GetInstance()->FindItemInInven(FindIndexVec2, &Item(_T("좀비눈알(청)"), _T("Item_Quest_7"), NULL, 0, ITEM_TYPE_QUEST, QUEST_ID_7, -1, -1, 1, 1, 2, 0, 1000, 1, 0, 0));

		// RemoveItemInInven
		CItemMgr::GetInstance()->RemoveItemInInven(FindIndexVec1[0]);
		CItemMgr::GetInstance()->RemoveItemInInven(FindIndexVec2[0]);
		CItemMgr::GetInstance()->CommitInven();

		// QuestAlarmMessage
		CQuestAlarmMessage* pQuestAlarmMessage = new CQuestAlarmMessage(NULL, OBJ_TYPE_DYNAMIC, _T("메인퀘스트5 : 마을의 평화"));
		m_pLayer->AddObject(pQuestAlarmMessage, LAYER_TYPE_UI);
		pQuestAlarmMessage->Initialize();

		// AddAchieve
		CQuestMgr::GetInstance()->AddAchieve(new Achieve(ACHIEVE_TYPE_MAIN_QUEST5));

		// Quest
		Quest* pQuest = CQuestMgr::GetInstance()->GetQuest(QUEST_TYPE_MAIN);
		pQuest->iStep = 5;

		// NPCVec
		vector<CObject*> NPCVec;
		m_pLayer->FindObjects(NPCVec, _T("NPC"), LAYER_TYPE_NPC);

		for(size_t i = 0; i < NPCVec.size(); ++i)
		{
			CNPC* pNPC = (CNPC*)NPCVec[i];
			if(pNPC->GetNPCType() == NPC_TYPE_TRISTRAM_TASHUN)
			{
				pNPC->SetMode(4);
				break;
			}
		}

		Destroy();
	}
}