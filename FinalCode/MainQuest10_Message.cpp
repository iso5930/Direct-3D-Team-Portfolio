#include "StdAfx.h"
#include "MainQuest10_Message.h"

CMainQuest10_Message::CMainQuest10_Message(TCHAR* _tszObjKey, OBJ_TYPE _eObjType)
: CQuestMessage(_tszObjKey, _eObjType)
{
	// Mode
	m_iMode = 0;

	// Name
	_tcscpy_s(m_tszName, MIN_STR, _T("죽어가는 가드"));

	// Text
	_tcscpy_s(m_tszText, MAX_STR, _T("끄..으으.."));
}

CMainQuest10_Message::~CMainQuest10_Message()
{
	Release();
}

void CMainQuest10_Message::Initialize()
{
	CQuestMessage::Initialize();

	CTransformCom* pTransformCom;

	// PortraitSign
	m_pPortraitSign = new CPortraitSign(NULL, OBJ_TYPE_STATIC, _T("Sign_Guard2"));
	m_pLayer->AddObject(m_pPortraitSign, LAYER_TYPE_UI);

	pTransformCom = (CTransformCom*)m_pPortraitSign->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(-0.305f, -0.592f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.118006f, 0.187f, 0.0f);

	m_pPortraitSign->Initialize();
}

int CMainQuest10_Message::Update()
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

void CMainQuest10_Message::Render()
{
	CQuestMessage::Render();
}

void CMainQuest10_Message::Release()
{
}

void CMainQuest10_Message::Mode0()
{
	if(m_pXButton->IsLUp())
	{
		Item* pItem = new Item(_T("열쇠"), _T("Item_Quest_6"), NULL, 0, ITEM_TYPE_QUEST, QUEST_ID_6, -1, -1, 1, 1, 2, 0, 1000, 1, 0, 0);

		if(CItemMgr::GetInstance()->AddItemInInven(pItem))
		{
			// Text
			_tcscpy_s(m_tszText, MAX_STR, _T("장로님이.. 장로님이 위험합니다. 침입자가 있소. 이 열쇠는 장로\n님 방으로 들어갈 수 있는 열쇠요. 서두르시오.."));

			// Mode
			m_iMode = 1;

			CItemMgr::GetInstance()->CommitInven();
		}
		else
		{
			// Text
			_tcscpy_s(m_tszText, MAX_STR, _T("드릴 것이 있으니 보관함을 비우고 다시 말을 걸어주세요."));

			// Mode
			m_iMode = 2;

			delete pItem;
			CItemMgr::GetInstance()->RollbackInven();
		}
	}
}

void CMainQuest10_Message::Mode1()
{
	if(m_pXButton->IsLUp())
	{
		// QuestAlarmMessage
		CQuestAlarmMessage* pQuestAlarmMessage = new CQuestAlarmMessage(NULL, OBJ_TYPE_DYNAMIC, _T("메인퀘스트10 : 침입자"));
		m_pLayer->AddObject(pQuestAlarmMessage, LAYER_TYPE_UI);
		pQuestAlarmMessage->Initialize();

		// AddAchieve
		CQuestMgr::GetInstance()->AddAchieve(new Achieve(ACHIEVE_TYPE_MAIN_QUEST10));

		// Quest
		Quest* pQuest = CQuestMgr::GetInstance()->GetQuest(QUEST_TYPE_MAIN);
		pQuest->iStep = 10;

		// StaticProbVec
		vector<CObject*> StaticProbVec;
		m_pLayer->FindObjects(StaticProbVec, _T("StaticProb"), LAYER_TYPE_STATIC_PROB);

		for(size_t i = 0; i < StaticProbVec.size(); ++i)
		{
			CStaticProb* pStaticProb = (CStaticProb*)StaticProbVec[i];
			if(pStaticProb->GetProbType() == PROB_TYPE_CATHEDRAL_DEATH_GAURD)
			{
				pStaticProb->EventEnd();
				break;
			}
		}

		// DynamicProbVec
		vector<CObject*> DynamicProbVec;
		m_pLayer->FindObjects(DynamicProbVec, _T("DynamicProb"), LAYER_TYPE_DYNAMIC_PROB);

		for(size_t i = 0; i < DynamicProbVec.size(); ++i)
		{
			CDynamicProb* pDynamicProb = (CDynamicProb*)DynamicProbVec[i];
			if(pDynamicProb->GetProbType() == PROB_TYPE_CATH1F_TO_CATH2F_DOOR)
			{
				pDynamicProb->Event();
				break;
			}
		}

		Destroy();
	}
}

void CMainQuest10_Message::Mode2()
{
	if(m_pXButton->IsLUp())
		Destroy();
}