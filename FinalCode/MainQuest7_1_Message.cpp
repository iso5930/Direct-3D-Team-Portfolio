#include "StdAfx.h"
#include "MainQuest7_1_Message.h"

CMainQuest7_1_Message::CMainQuest7_1_Message(TCHAR* _tszObjKey, OBJ_TYPE _eObjType)
: CQuestMessage(_tszObjKey, _eObjType)
{
	// Name
	_tcscpy_s(m_tszName, MIN_STR, _T("타스한"));

	// Text
	_tcscpy_s(m_tszText, MAX_STR, _T("제련해오지 않으면 의미가 없어! 품질이 않좋단 말여.. 품질이!"));
}

CMainQuest7_1_Message::~CMainQuest7_1_Message()
{
	Release();
}

void CMainQuest7_1_Message::Initialize()
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

int CMainQuest7_1_Message::Update()
{
	CQuestMessage::Update();

	if(m_pXButton->IsLUp())
		Destroy();

	return 0;
}

void CMainQuest7_1_Message::Render()
{
	CQuestMessage::Render();
}

void CMainQuest7_1_Message::Release()
{
}