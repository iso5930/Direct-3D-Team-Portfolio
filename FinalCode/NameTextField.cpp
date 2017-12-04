#include "StdAfx.h"
#include "NameTextField.h"

CNameTextField::CNameTextField(TCHAR* _tszObjKey, OBJ_TYPE _eObjType)
: CTextFieldUI(_tszObjKey, _eObjType, _T("TextField_Back_Name"), _T("TextField_Over_Name"))
{
	// Pos
	m_pTransformCom->m_vPos = D3DXVECTOR3(0.0f, -0.625f, 0.0f);

	// Size
	m_pTransformCom->m_vSize = D3DXVECTOR3(0.4083f, 0.08666f, 0.0f);
}

CNameTextField::~CNameTextField()
{
	Release();
}

void CNameTextField::Initialize()
{
	CTextFieldUI::Initialize();
}

int CNameTextField::Update()
{
	CTextFieldUI::Update();
	return 0;
}

void CNameTextField::Render()
{
	CTextFieldUI::Render();

	RECT rcText;
	SetRect(&rcText, 530, 577, WINCX, WINCY);
	CFontMgr::GetInstance()->GetBauhaus(16, 8)->DrawText(NULL, m_tszText, -1, &rcText, DT_LEFT, D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
	CFontMgr::GetInstance()->GetBauhaus(16, 8)->DrawText(NULL, m_tszText, -1, &rcText, DT_CALCRECT, D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));

	m_iWidth = rcText.right - rcText.left;
	m_iHeight = rcText.bottom - rcText.top;
}

void CNameTextField::Release()
{
}