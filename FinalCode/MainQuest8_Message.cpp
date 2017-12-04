#include "StdAfx.h"
#include "MainQuest8_Message.h"

CMainQuest8_Message::CMainQuest8_Message(TCHAR* _tszObjKey, OBJ_TYPE _eObjType)
: CQuestMessage(_tszObjKey, _eObjType)
{
	// Mode
	m_iMode = 0;

	// Name
	_tcscpy_s(m_tszName, MIN_STR, _T("Ÿ����"));

	// Text
	_tcscpy_s(m_tszText, MAX_STR, _T("���� �������� �±���!"));
}

CMainQuest8_Message::~CMainQuest8_Message()
{
	Release();
}

void CMainQuest8_Message::Initialize()
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

int CMainQuest8_Message::Update()
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

void CMainQuest8_Message::Render()
{
	CQuestMessage::Render();
}

void CMainQuest8_Message::Release()
{
}

void CMainQuest8_Message::Mode0()
{
	if(m_pXButton->IsLUp())
	{
		_tcscpy_s(m_tszText, MAX_STR, _T("�嵥.. �̹� ���� �뺴���� �������ȴٳ�.. �ʹ� �ʾ���...."));
		m_iMode = 1;
	}
}

void CMainQuest8_Message::Mode1()
{
	if(m_pXButton->IsLUp())
	{
		// QuestAlarmMessage
		CQuestAlarmMessage* pQuestAlarmMessage = new CQuestAlarmMessage(NULL, OBJ_TYPE_DYNAMIC, _T("��������Ʈ8 : �ʹ� �ʾ���"));
		m_pLayer->AddObject(pQuestAlarmMessage, LAYER_TYPE_UI);
		pQuestAlarmMessage->Initialize();

		// AddAchieve
		CQuestMgr::GetInstance()->AddAchieve(new Achieve(ACHIEVE_TYPE_MAIN_QUEST8));

		// Quest
		Quest* pQuest = CQuestMgr::GetInstance()->GetQuest(QUEST_TYPE_MAIN);
		pQuest->iStep = 8;

		// NPCVec
		vector<CObject*> NPCVec;
		m_pLayer->FindObjects(NPCVec, _T("NPC"), LAYER_TYPE_NPC);

		for(size_t i = 0; i < NPCVec.size(); ++i)
		{
			CNPC* pNPC = (CNPC*)NPCVec[i];
			if(pNPC->GetNPCType() == NPC_TYPE_TRISTRAM_TASHUN)
			{
				pNPC->SetMode(8);
				break;
			}
		}

		Destroy();
	}
}