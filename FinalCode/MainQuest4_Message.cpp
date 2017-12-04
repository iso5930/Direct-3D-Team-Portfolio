#include "StdAfx.h"
#include "MainQuest4_Message.h"

CMainQuest4_Message::CMainQuest4_Message(TCHAR* _tszObjKey, OBJ_TYPE _eObjType)
: CQuestMessage(_tszObjKey, _eObjType)
{
	// Mode
	m_iMode = 0;

	// Name
	_tcscpy_s(m_tszName, MIN_STR, _T("Ÿ����"));

	// Text
	_tcscpy_s(m_tszText, MAX_STR, _T("�ڳ׵� �˴ٽ���.. ���� ��� Ʈ����Ʈ�� �αٿ� ���� ����\n�����ϰ� �ִٳ�.."));
}

CMainQuest4_Message::~CMainQuest4_Message()
{
	Release();
}

void CMainQuest4_Message::Initialize()
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

int CMainQuest4_Message::Update()
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
	}

	return 0;
}

void CMainQuest4_Message::Render()
{
	CQuestMessage::Render();
}

void CMainQuest4_Message::Release()
{
}

void CMainQuest4_Message::Mode0()
{
	if(m_pXButton->IsLUp())
	{
		_tcscpy_s(m_tszText, MAX_STR, _T("ù ��° �ӹ��� ���� óġ�ϼ�. ���� ����ϴٺ��� ���񴫾���\n���� �� �����ɼ�. ���񴫾�(��)�� ���񴫾�(û)�� �������� �ǳ�."));
		m_iMode = 1;
	}
}

void CMainQuest4_Message::Mode1()
{
	if(m_pXButton->IsLUp())
	{
		// QuestAlarmMessage
		CQuestAlarmMessage* pQuestAlarmMessage = new CQuestAlarmMessage(NULL, OBJ_TYPE_DYNAMIC, _T("��������Ʈ4 : ù ��° �ӹ�"));
		m_pLayer->AddObject(pQuestAlarmMessage, LAYER_TYPE_UI);
		pQuestAlarmMessage->Initialize();

		// AddAchieve
		CQuestMgr::GetInstance()->AddAchieve(new Achieve(ACHIEVE_TYPE_MAIN_QUEST4));

		// Quest
		Quest* pQuest = CQuestMgr::GetInstance()->GetQuest(QUEST_TYPE_MAIN);
		pQuest->iStep = 4;

		// NPCVec
		vector<CObject*> NPCVec;
		m_pLayer->FindObjects(NPCVec, _T("NPC"), LAYER_TYPE_NPC);

		for(size_t i = 0; i < NPCVec.size(); ++i)
		{
			CNPC* pNPC = (CNPC*)NPCVec[i];
			if(pNPC->GetNPCType() == NPC_TYPE_TRISTRAM_TASHUN)
			{
				pNPC->SetMode(3);
				break;
			}
		}

		// StaticProbVec
		vector<CObject*> StaticProbVec;
		m_pLayer->FindObjects(StaticProbVec, _T("StaticProb"), LAYER_TYPE_STATIC_PROB);

		for(size_t i = 0; i < StaticProbVec.size(); ++i)
		{
			CStaticProb* pStaticProb = (CStaticProb*)StaticProbVec[i];
			if(pStaticProb->GetProbType() == PROB_TYPE_TRISTRAM_WAGON_DESTROYED)
			{
				pStaticProb->Destroy();
				break;
			}
		}

		Destroy();
	}
}