#include "StdAfx.h"
#include "IDTextField.h"

CIDTextField::CIDTextField(TCHAR* _tszObjKey, OBJ_TYPE _eObjType)
: CTextFieldUI(_tszObjKey, _eObjType, _T("TextField_Back_ID"), _T("TextField_Over_ID"))
{
	// Pos
	m_pTransformCom->m_vPos = D3DXVECTOR3(0.0f, -0.1f, 0.0f);

	// Size
	m_pTransformCom->m_vSize = D3DXVECTOR3(0.4083f, 0.08666f, 0.0f);
}

CIDTextField::~CIDTextField()
{
	Release();
}

void CIDTextField::Initialize()
{
	CTextFieldUI::Initialize();
}

int CIDTextField::Update()
{
	CTextFieldUI::Update();
	return 0;
}

void CIDTextField::Render()
{
	CTextFieldUI::Render();

	RECT rcText;
	SetRect(&rcText, 530, 387, WINCX, WINCY);
	CFontMgr::GetInstance()->GetBauhaus(16, 8)->DrawText(NULL, m_tszText, -1, &rcText, DT_LEFT, D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
	CFontMgr::GetInstance()->GetBauhaus(16, 8)->DrawText(NULL, m_tszText, -1, &rcText, DT_CALCRECT, D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));

	m_iWidth = rcText.right - rcText.left;
	m_iHeight = rcText.bottom - rcText.top;
}

void CIDTextField::Release()
{
}