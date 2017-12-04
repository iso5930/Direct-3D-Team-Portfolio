#include "StdAfx.h"
#include "MainQuest2_1_Message.h"

CMainQuest2_1_Message::CMainQuest2_1_Message(TCHAR* _tszObjKey, OBJ_TYPE _eObjType)
: CQuestMessage(_tszObjKey, _eObjType)
{
	// Mode
	m_iMode = 0;

	// Name
	_tcscpy_s(m_tszName, MIN_STR, _T("���"));

	// Text
	_tcscpy_s(m_tszText, MAX_STR, _T("�Ⱬ�쵢�̱��� ��Ÿ���ٴ�.. ���п� ����� ������ �� �־�����\n��."));
}

CMainQuest2_1_Message::~CMainQuest2_1_Message()
{
	Release();
}

void CMainQuest2_1_Message::Initialize()
{
	CQuestMessage::Initialize();

	// TransformCom
	CTransformCom* pTransformCom;

	// PortraitSign
	m_pPortraitSign = new CPortraitSign(NULL, OBJ_TYPE_STATIC, _T("Sign_Guard1"));
	m_pLayer->AddObject(m_pPortraitSign, LAYER_TYPE_UI);

	pTransformCom = (CTransformCom*)m_pPortraitSign->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(-0.305f, -0.592f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.118006f, 0.187f, 0.0f);

	m_pPortraitSign->Initialize();
}

int CMainQuest2_1_Message::Update()
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

void CMainQuest2_1_Message::Render()
{
	CQuestMessage::Render();
}

void CMainQuest2_1_Message::Release()
{
}

void CMainQuest2_1_Message::Mode0()
{
	if(m_pXButton->IsLUp())
	{
		Item* pItem = new Item(_T("����༭"), _T("Item_Quest_3"), NULL, 0, ITEM_TYPE_QUEST, QUEST_ID_3, -1, -1, 1, 1, 2, 0, 10000, 1, 0, 0);

		if(CItemMgr::GetInstance()->AddItemInInven(pItem))
		{
			// Text
			_tcscpy_s(m_tszText, MAX_STR, _T("�� ����༭�� ������ ���� ����Բ� ��������. ������ �����!"));

			// Mode
			m_iMode = 1;

			CItemMgr::GetInstance()->CommitInven();
		}
		else
		{
			// Text
			_tcscpy_s(m_tszText, MAX_STR, _T("�帱 ���� ������ �������� ���� �ٽ� ���� �ɾ��ּ���."));

			// Mode
			m_iMode = 2;

			delete pItem;
			CItemMgr::GetInstance()->RollbackInven();
		}
	}
}

void CMainQuest2_1_Message::Mode1()
{
	if(m_pXButton->IsLUp())
	{
		// QuestAlarmMessage
		CQuestAlarmMessage* pQuestAlarmMessage = new CQuestAlarmMessage(NULL, OBJ_TYPE_DYNAMIC, _T("��������Ʈ2 : Ʈ����Ʈ�� �Լ�"));
		m_pLayer->AddObject(pQuestAlarmMessage, LAYER_TYPE_UI);
		pQuestAlarmMessage->Initialize();

		// AddAchieve
		CQuestMgr::GetInstance()->AddAchieve(new Achieve(ACHIEVE_TYPE_MAIN_QUEST2));

		// Quest
		Quest* pQuest = CQuestMgr::GetInstance()->GetQuest(QUEST_TYPE_MAIN);
		pQuest->iStep = 2;

		// NPCVec
		vector<CObject*> NPCVec;
		m_pLayer->FindObjects(NPCVec, _T("NPC"), LAYER_TYPE_NPC);

		for(size_t i = 0; i < NPCVec.size(); ++i)
		{
			CNPC* pNPC = (CNPC*)NPCVec[i];
			if(pNPC->GetNPCType() == NPC_TYPE_TRISTRAM_GUARD)
			{
				pNPC->SetMode(0);
				break;
			}
		}

		for(size_t i = 0; i < NPCVec.size(); ++i)
		{
			CNPC* pNPC = (CNPC*)NPCVec[i];
			if(pNPC->GetNPCType() == NPC_TYPE_TRISTRAM_TASHUN)
			{
				pNPC->SetMode(1);
				break;
			}
		}

		// DynamicProbVec
		vector<CObject*> DynamicProbVec;
		m_pLayer->FindObjects(DynamicProbVec, _T("DynamicProb"), LAYER_TYPE_DYNAMIC_PROB);

		for(size_t i = 0; i < DynamicProbVec.size(); ++i)
		{
			CDynamicProb* pDynamicProb = (CDynamicProb*)DynamicProbVec[i];
			if(pDynamicProb->GetProbType() == PROB_TYPE_TRISTRAM_GATE_TOWN)
			{
				pDynamicProb->Event();
				break;
			}
		}

		Destroy();
	}
}

void CMainQuest2_1_Message::Mode2()
{
	if(m_pXButton->IsLUp())
		Destroy();
}