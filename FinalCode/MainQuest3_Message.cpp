#include "StdAfx.h"
#include "MainQuest3_Message.h"

CMainQuest3_Message::CMainQuest3_Message(TCHAR* _tszObjKey, OBJ_TYPE _eObjType)
: CQuestMessage(_tszObjKey, _eObjType)
{
	// Mode
	m_iMode = 0;

	// Name
	_tcscpy_s(m_tszName, MIN_STR, _T("타스한"));

	// Text
	_tcscpy_s(m_tszText, MAX_STR, _T("허허~ 트리스트럼에 온걸 환영하오!"));
}

CMainQuest3_Message::~CMainQuest3_Message()
{
	Release();
}

void CMainQuest3_Message::Initialize()
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

int CMainQuest3_Message::Update()
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

	case 4:
		Mode4();
		break;

	case 5:
		Mode5();
		break;
	}

	return 0;
}

void CMainQuest3_Message::Render()
{
	CQuestMessage::Render();
}

void CMainQuest3_Message::Release()
{
}

void CMainQuest3_Message::Mode0()
{
	if(m_pXButton->IsLUp())
	{
		_tcscpy_s(m_tszText, MAX_STR, _T("용병이 되기 위해 왔다지? 어디 고용계약서를 좀 봅세."));
		m_iMode = 1;
	}
}

void CMainQuest3_Message::Mode1()
{
	if(m_pXButton->IsLUp())
	{
		// FindIndexVec
		vector<int> FindIndexVec;
		CItemMgr::GetInstance()->FindItemInInven(FindIndexVec, &Item(_T("고용계약서"), _T("Item_Quest_3"), NULL, 0, ITEM_TYPE_QUEST, QUEST_ID_3, -1, -1, 1, 1, 2, 0, 10000, 1, 0, 0));

		if(FindIndexVec.size() > 0)
		{
			// FindObject
			CObject* pFindObject = NULL;
			m_pLayer->FindObject(pFindObject, _T("Player"), LAYER_TYPE_PLAYER);

			CPlayer* pPlayer = (CPlayer*)pFindObject;

			_tcscpy_s(m_tszText, MAX_STR, _T("이름이 "));
			_tcscat_s(m_tszText, MAX_STR, pPlayer->GetInfo()->tszName);
			_tcscat_s(m_tszText, MAX_STR, _T("이구먼..\n트리스트럼을 위해 일할 준비가 되었는가?"));
			m_iMode = 2;
		}
		else
		{
			_tcscpy_s(m_tszText, MAX_STR, _T("고용계약서를 잃어버렸다고? 너무 걱정말게, 내 10000골드에\n판매하고 있네. 사시겠는가?"));
			m_iMode = 4;
		}
	}
}

void CMainQuest3_Message::Mode2()
{
	if(m_pXButton->IsLUp())
	{
		_tcscpy_s(m_tszText, MAX_STR, _T("용병계약이 완료되었네! 축하하네. 최선을 다해주게.."));
		m_iMode = 3;
	}
}

void CMainQuest3_Message::Mode3()
{
	if(m_pXButton->IsLUp())
	{
		// FindIndexVec
		vector<int> FindIndexVec;
		CItemMgr::GetInstance()->FindItemInInven(FindIndexVec, &Item(_T("고용계약서"), _T("Item_Quest_3"), NULL, 0, ITEM_TYPE_QUEST, QUEST_ID_3, -1, -1, 1, 1, 2, 0, 10000, 1, 0, 0));

		// RemoveItem
		CItemMgr::GetInstance()->RemoveItemInInven(FindIndexVec[0]);
		CItemMgr::GetInstance()->CommitInven();

		// QuestAlarmMessage
		CQuestAlarmMessage* pQuestAlarmMessage = new CQuestAlarmMessage(NULL, OBJ_TYPE_DYNAMIC, _T("메인퀘스트3 : 용병계약 완료"));
		m_pLayer->AddObject(pQuestAlarmMessage, LAYER_TYPE_UI);
		pQuestAlarmMessage->Initialize();

		// AddAchieve
		CQuestMgr::GetInstance()->AddAchieve(new Achieve(ACHIEVE_TYPE_MAIN_QUEST3));

		// NPCVec
		vector<CObject*> NPCVec;
		m_pLayer->FindObjects(NPCVec, _T("NPC"), LAYER_TYPE_NPC);

		for(size_t i = 0; i < NPCVec.size(); ++i)
		{
			CNPC* pNPC = (CNPC*)NPCVec[i];
			if(pNPC->GetNPCType() == NPC_TYPE_TRISTRAM_TASHUN)
			{
				pNPC->SetMode(2);
				break;
			}
		}

		// Quest
		Quest* pQuest = CQuestMgr::GetInstance()->GetQuest(QUEST_TYPE_MAIN);
		pQuest->iStep = 3;

		Destroy();
	}
}

void CMainQuest3_Message::Mode4()
{
	if(m_pXButton->IsLUp())
	{
		int iGold = CItemMgr::GetInstance()->GetGold();

		if(iGold >= 10000)
		{
			// Item
			Item* pItem = new Item(_T("고용계약서"), _T("Item_Quest_3"), NULL, 0, ITEM_TYPE_QUEST, QUEST_ID_3, -1, -1, 1, 1, 2, 0, 10000, 1, 0, 0);

			if(CItemMgr::GetInstance()->AddItemInInven(pItem))
			{
				CItemMgr::GetInstance()->SetGold(iGold - 10000);
				CItemMgr::GetInstance()->CommitInven();

				_tcscpy_s(m_tszText, MAX_STR, _T("여기 고용계약서가 있네. 다시 말을 걸어주시게."));
				m_iMode = 5;
			}
			else
			{
				delete pItem;
				CItemMgr::GetInstance()->RollbackInven();

				_tcscpy_s(m_tszText, MAX_STR, _T("보관함이 공간이 부족하네. 보관함을 비우고 오시게."));
				m_iMode = 5;
			}
		}
		else
		{
			_tcscpy_s(m_tszText, MAX_STR, _T("골드가 부족하네. 골드를 모아오시게."));
			m_iMode = 5;
		}
	}
}

void CMainQuest3_Message::Mode5()
{
	if(m_pXButton->IsLUp())
		Destroy();
}