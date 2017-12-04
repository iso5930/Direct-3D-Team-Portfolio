#include "StdAfx.h"
#include "MainQuest2_Message.h"

CMainQuest2_Message::CMainQuest2_Message(TCHAR* _tszObjKey, OBJ_TYPE _eObjType)
: CQuestMessage(_tszObjKey, _eObjType)
{
	// Mode
	m_iMode = 0;

	// Name
	_tcscpy_s(m_tszName, MIN_STR, _T("경비병"));

	// Text
	_tcscpy_s(m_tszText, MAX_STR, _T("예언자 마스티나님께 이야기 들었습니다. 실력이 뛰어난 용병이\n시라구요? 반갑습니다. 저는 트리스트럼 경비병입니다. 요즘\n유난히 좀비가 많아져서 용병을 모집하고 있습니다. 세상이 참..."));
}

CMainQuest2_Message::~CMainQuest2_Message()
{
	Release();
}

void CMainQuest2_Message::Initialize()
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

int CMainQuest2_Message::Update()
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

void CMainQuest2_Message::Render()
{
	CQuestMessage::Render();
}

void CMainQuest2_Message::Release()
{
}

void CMainQuest2_Message::Mode0()
{
	if(m_pXButton->IsLUp())
	{
		_tcscpy_s(m_tszText, MAX_STR, _T("이런! 또, 좀비가 나타났군. 아직 고용한건 아니지만 좀 도와주면\n안되겠습니까?"));
		++m_iMode;
	}
}

void CMainQuest2_Message::Mode1()
{
	if(m_pXButton->IsLUp())
	{
		// MainQuest2_Trigger
		CMainQuest2_Trigger* pMainQuest2_Trigger = new CMainQuest2_Trigger(NULL, OBJ_TYPE_DYNAMIC);
		m_pLayer->AddObject(pMainQuest2_Trigger, LAYER_TYPE_TRIGGER);
		pMainQuest2_Trigger->Initialize();

		// NPCVec
		vector<CObject*> NPCVec;
		m_pLayer->FindObjects(NPCVec, _T("NPC"), LAYER_TYPE_NPC);

		for(size_t i = 0; i < NPCVec.size(); ++i)
		{
			CNPC* pNPC = (CNPC*)NPCVec[i];
			if(pNPC->GetNPCType() == NPC_TYPE_TRISTRAM_GUARD)
			{
				pNPC->SetMode(-1);
				break;
			}
		}

		Destroy();
	}
}