#include "StdAfx.h"
#include "CharacterFullMessage.h"

CCharacterFullMessage::CCharacterFullMessage(TCHAR* _tszObjKey, OBJ_TYPE _eObjType)
: CMessageUI(_tszObjKey, _eObjType, _T("Message_CharacterFull"))
{
	// Text
	_tcscpy_s(m_tszText, MAX_STR, _T("더 이상 생성할 수 없습니다."));

	// Size
	m_pTransformCom->m_vSize = D3DXVECTOR3(0.5f, 0.5f, 0.0f);
}

CCharacterFullMessage::~CCharacterFullMessage()
{
	Release();
}

void CCharacterFullMessage::Initialize()
{
	CMessageUI::Initialize();

	// TransformCom
	CTransformCom* pTransformCom;

	// CloseButton
	m_pCloseButton = new CBasicButton(NULL, OBJ_TYPE_DYNAMIC, _T("Button_Back_Close"), _T("Button_Over_Close"), _T("Button_Down_Close"));
	m_pLayer->AddObject(m_pCloseButton, LAYER_TYPE_UI);
	pTransformCom = (CTransformCom*)m_pCloseButton->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(0.0f, -0.165f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.3f, 0.09f, 0.0f);
	m_pCloseButton->Initialize();
}

int CCharacterFullMessage::Update()
{
	CMessageUI::Update();

	CInputMgr::GetInstance()->KeyInvalidate();
	CInputMgr::GetInstance()->MousePosInvalidate();
	CInputMgr::GetInstance()->MouseInvalidate();

	return 0;
}

void CCharacterFullMessage::Render()
{
	CMessageUI::Render();

	RECT rcText;
	SetRect(&rcText, 0, 340, WINCX, WINCY);
	CFontMgr::GetInstance()->GetBauhaus(20, 8)->DrawText(NULL, m_tszText, -1, &rcText, DT_CENTER, D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
}

void CCharacterFullMessage::Release()
{
}