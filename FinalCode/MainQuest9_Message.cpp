#include "StdAfx.h"
#include "MainQuest9_Message.h"

CMainQuest9_Message::CMainQuest9_Message(TCHAR* _tszObjKey, OBJ_TYPE _eObjType)
: CQuestMessage(_tszObjKey, _eObjType)
{
	// Mode
	m_iMode = 0;

	// Name
	_tcscpy_s(m_tszName, MIN_STR, _T("타스한"));

	// Text
	_tcscpy_s(m_tszText, MAX_STR, _T("큰일났네! 자네밖에 도와줄 사람이 없어!"));
}

CMainQuest9_Message::~CMainQuest9_Message()
{
	Release();
}

void CMainQuest9_Message::Initialize()
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

int CMainQuest9_Message::Update()
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

void CMainQuest9_Message::Render()
{
	CQuestMessage::Render();
}

void CMainQuest9_Message::Release()
{
}

void CMainQuest9_Message::Mode0()
{
	if(m_pXButton->IsLUp())
	{
		_tcscpy_s(m_tszText, MAX_STR, _T("몇일 전부터 레오릭 장로님이 보이질 않네. 많은 용병들을 장로님\n집에 보내봤지만 그들도 돌아오질 않고 있네."));
		m_iMode = 1;
	}
}

void CMainQuest9_Message::Mode1()
{
	if(m_pXButton->IsLUp())
	{
		_tcscpy_s(m_tszText, MAX_STR, _T("반드시 무슨 일이 생긴 것이 분명해! 자네가 가봐주면 안되겠나?"));
		m_iMode = 2;
	}
}

void CMainQuest9_Message::Mode2()
{
	if(m_pXButton->IsLUp())
	{
		// QuestAlarmMessage
		CQuestAlarmMessage* pQuestAlarmMessage = new CQuestAlarmMessage(NULL, OBJ_TYPE_DYNAMIC, _T("메인퀘스트9 : 장로 실종"));
		m_pLayer->AddObject(pQuestAlarmMessage, LAYER_TYPE_UI);
		pQuestAlarmMessage->Initialize();

		// AddAchieve
		CQuestMgr::GetInstance()->AddAchieve(new Achieve(ACHIEVE_TYPE_MAIN_QUEST9));

		// Quest
		Quest* pQuest = CQuestMgr::GetInstance()->GetQuest(QUEST_TYPE_MAIN);
		pQuest->iStep = 9;

		// NPCVec
		vector<CObject*> NPCVec;
		m_pLayer->FindObjects(NPCVec, _T("NPC"), LAYER_TYPE_NPC);

		for(size_t i = 0; i < NPCVec.size(); ++i)
		{
			CNPC* pNPC = (CNPC*)NPCVec[i];
			if(pNPC->GetNPCType() == NPC_TYPE_TRISTRAM_TASHUN)
			{
				pNPC->SetMode(9);
				break;
			}
		}

		// DynamicProbVec
		vector<CObject*> DynamicProbVec;
		m_pLayer->FindObjects(DynamicProbVec, _T("DynamicProb"), LAYER_TYPE_DYNAMIC_PROB);

		for(size_t i = 0; i < DynamicProbVec.size(); ++i)
		{
			CDynamicProb* pDynamicProb = (CDynamicProb*)DynamicProbVec[i];
			if(pDynamicProb->GetProbType() == PROB_TYPE_TRISTRAM_TO_CATH1F_DOOR)
			{
				pDynamicProb->Event();
				break;
			}
		}

		Destroy();
	}
}