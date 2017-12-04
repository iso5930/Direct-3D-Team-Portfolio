#include "StdAfx.h"
#include "QuestMessage.h"

CQuestMessage::CQuestMessage(TCHAR* _tszObjKey, OBJ_TYPE _eObjType)
: CMessageUI(_tszObjKey, _eObjType, _T("Message_QuestBox"))
{
	// Name
	ZeroMemory(m_tszName, sizeof(m_tszName));

	// XButton
	m_pXButton = NULL;

	//PortraitSign
	m_pPortraitSign = NULL;

	// Pos
	m_pTransformCom->m_vPos = D3DXVECTOR3(-0.02f, -0.589f, 0.0f);

	// Size
	m_pTransformCom->m_vSize = D3DXVECTOR3(0.735f, 0.278f, 0.0f);
}

CQuestMessage::~CQuestMessage()
{
	Release();
}

void CQuestMessage::Initialize()
{
	CMessageUI::Initialize();

	// TransformCom
	CTransformCom* pTransformCom;

	// XButton
	m_pXButton = new CBasicButton(NULL, OBJ_TYPE_DYNAMIC, _T("Button_Back_X"), _T("Button_Over_X"), _T("Button_Down_X"));
	m_pLayer->AddObject(m_pXButton, LAYER_TYPE_UI);
	pTransformCom = (CTransformCom*)m_pXButton->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(0.318f, -0.525f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.029f, 0.052f, 0.0f);
	m_pXButton->Initialize();

	CUpdateCom* pUpdateCom = (CUpdateCom*)m_pXButton->GetComponent(COM_TYPE_UPDATE);
	if(pUpdateCom != NULL)
		pUpdateCom->m_dwPriority = 0xFFFFFFFB;

	CRenderCom* pRenderCom = (CRenderCom*)m_pXButton->GetComponent(COM_TYPE_RENDER);
	if(pRenderCom != NULL)
		pRenderCom->m_dwPriority = 0x00000004;

	// DeleteWindow
	for(int i = 0; i < WINDOW_TYPE_END; ++i)
	{
		if(i == WINDOW_TYPE_SLOT)
			continue;

		if(CUIMgr::GetInstance()->GetWindow((WINDOW_TYPE)i) != NULL)
		{
			CInputMgr::GetInstance()->KeyStop(DIK_ESCAPE);
			CUIMgr::GetInstance()->DeleteWindow((WINDOW_TYPE)i);
		}
	}
}

int CQuestMessage::Update()
{
	CMessageUI::Update();

	CUpdateCom* pUpdateCom = (CUpdateCom*)m_pXButton->GetComponent(COM_TYPE_UPDATE);
	if(pUpdateCom != NULL)
		pUpdateCom->m_dwPriority = 0xFFFFFFFB;

	CRenderCom* pRenderCom = (CRenderCom*)m_pXButton->GetComponent(COM_TYPE_RENDER);
	if(pRenderCom != NULL)
		pRenderCom->m_dwPriority = 0x00000004;

	CInputMgr::GetInstance()->KeyInvalidate();
	CInputMgr::GetInstance()->MouseInvalidate();
	CInputMgr::GetInstance()->MousePosInvalidate();

	return 0;
}

void CQuestMessage::Render()
{
	CMessageUI::Render();

	RECT rcText;
	SetRect(&rcText, 500, 543, 900, 557);
	CFontMgr::GetInstance()->GetBauhaus(14, 7)->DrawText(NULL, m_tszName, -1, &rcText, DT_LEFT, D3DXCOLOR(0.85098f, 0.6f, 0.247058f, 1.0f));

	SetRect(&rcText, 500, 563, 900, 599);
	CFontMgr::GetInstance()->GetBauhaus(12, 6)->DrawText(NULL, m_tszText, -1, &rcText, DT_LEFT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
}

void CQuestMessage::Release()
{
	// XButton
	if(m_pXButton != NULL)
	{
		m_pXButton->Destroy();
		m_pXButton = NULL;
	}

	//PortraitSign
	if(m_pPortraitSign != NULL)
	{
		m_pPortraitSign->Destroy();
		m_pPortraitSign = NULL;
	}
}