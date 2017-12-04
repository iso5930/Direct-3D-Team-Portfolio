#include "StdAfx.h"
#include "PWTextField.h"

CPWTextField::CPWTextField(TCHAR* _tszObjKey, OBJ_TYPE _eObjType)
: CTextFieldUI(_tszObjKey, _eObjType, _T("TextField_Back_ID"), _T("TextField_Over_ID"))
{
	// Pos
	m_pTransformCom->m_vPos = D3DXVECTOR3(0.0f, -0.31f, 0.0f);

	// Size
	m_pTransformCom->m_vSize = D3DXVECTOR3(0.4083f, 0.08666f, 0.0f);
}

CPWTextField::~CPWTextField()
{
	Release();
}

void CPWTextField::Initialize()
{
	CTextFieldUI::Initialize();
}

int CPWTextField::Update()
{
	CTextFieldUI::Update();
	return 0;
}

void CPWTextField::Render()
{
	CTextFieldUI::Render();

	TCHAR tszPW[MAX_STR];
	for(int i = 0; i < m_iCnt; ++i)
		tszPW[i] = _T('*');
	tszPW[m_iCnt] = _T('\0');

	RECT rcText;
	SetRect(&rcText, 530, 465, WINCX, WINCY);
	CFontMgr::GetInstance()->GetBauhaus(16, 8)->DrawText(NULL, tszPW, -1, &rcText, DT_LEFT, D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
	CFontMgr::GetInstance()->GetBauhaus(16, 8)->DrawText(NULL, tszPW, -1, &rcText, DT_CALCRECT, D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));

	m_iWidth = rcText.right - rcText.left;
	m_iHeight = rcText.bottom - rcText.top;
}

void CPWTextField::Release()
{
}