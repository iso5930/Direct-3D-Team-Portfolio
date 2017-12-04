#include "StdAfx.h"
#include "TextFieldUI.h"

CTextFieldUI::CTextFieldUI(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, TCHAR* _tszBackTexKey, TCHAR* _tszOverTexKey)
: CUI(_tszObjKey, _eObjType, _tszBackTexKey)
{
	// OverTexture
	m_pOverTexture = NULL;
	if(_tszOverTexKey != NULL)
		m_pOverTexture = CTextureMgr::GetInstance()->GetTexture(_tszOverTexKey);

	// Enable
	m_bEnable = false;

	// Text
	ZeroMemory(m_tszText, sizeof(m_tszText));

	// Cnt
	m_iCnt = 0;

	// Width
	m_iWidth = 0;

	// Height
	m_iHeight = 0;
}

CTextFieldUI::~CTextFieldUI()
{
	Release();
}

void CTextFieldUI::Initialize()
{
	CUI::Initialize();

	if(m_dwState & UI_OVER)
		m_pMaterialCom->m_pTexture = m_pOverTexture;
}

int CTextFieldUI::Update()
{
	CUI::Update();

	if(m_bEnable == false)
		return 0;

	if(CInputMgr::GetInstance()->KeyDown(DIK_BACK) && m_iCnt > 0)
		m_tszText[--m_iCnt] = _T('\0');

	if(CInputMgr::GetInstance()->KeyDown(DIK_0) && m_iCnt < 24)
		m_tszText[m_iCnt++] = _T('0');

	if(CInputMgr::GetInstance()->KeyDown(DIK_1) && m_iCnt < 24)
		m_tszText[m_iCnt++] = _T('1');

	if(CInputMgr::GetInstance()->KeyDown(DIK_2) && m_iCnt < 24)
		m_tszText[m_iCnt++] = _T('2');

	if(CInputMgr::GetInstance()->KeyDown(DIK_3) && m_iCnt < 24)
		m_tszText[m_iCnt++] = _T('3');

	if(CInputMgr::GetInstance()->KeyDown(DIK_4) && m_iCnt < 24)
		m_tszText[m_iCnt++] = _T('4');

	if(CInputMgr::GetInstance()->KeyDown(DIK_5) && m_iCnt < 24)
		m_tszText[m_iCnt++] = _T('5');

	if(CInputMgr::GetInstance()->KeyDown(DIK_6) && m_iCnt < 24)
		m_tszText[m_iCnt++] = _T('6');

	if(CInputMgr::GetInstance()->KeyDown(DIK_7) && m_iCnt < 24)
		m_tszText[m_iCnt++] = _T('7');

	if(CInputMgr::GetInstance()->KeyDown(DIK_8) && m_iCnt < 24)
		m_tszText[m_iCnt++] = _T('8');

	if(CInputMgr::GetInstance()->KeyDown(DIK_9) && m_iCnt < 24)
		m_tszText[m_iCnt++] = _T('9');

	if(CInputMgr::GetInstance()->KeyDown(DIK_A) && m_iCnt < 24)
	{
		if(CInputMgr::GetInstance()->KeyPress(DIK_LSHIFT) || CInputMgr::GetInstance()->KeyPress(DIK_RSHIFT))
			m_tszText[m_iCnt++] = _T('A');
		else
			m_tszText[m_iCnt++] = _T('a');
	}

	if(CInputMgr::GetInstance()->KeyDown(DIK_B) && m_iCnt < 24)
	{
		if(CInputMgr::GetInstance()->KeyPress(DIK_LSHIFT) || CInputMgr::GetInstance()->KeyPress(DIK_RSHIFT))
			m_tszText[m_iCnt++] = _T('B');
		else
			m_tszText[m_iCnt++] = _T('b');
	}

	if(CInputMgr::GetInstance()->KeyDown(DIK_C) && m_iCnt < 24)
	{
		if(CInputMgr::GetInstance()->KeyPress(DIK_LSHIFT) || CInputMgr::GetInstance()->KeyPress(DIK_RSHIFT))
			m_tszText[m_iCnt++] = _T('C');
		else
			m_tszText[m_iCnt++] = _T('c');
	}

	if(CInputMgr::GetInstance()->KeyDown(DIK_D) && m_iCnt < 24)
	{
		if(CInputMgr::GetInstance()->KeyPress(DIK_LSHIFT) || CInputMgr::GetInstance()->KeyPress(DIK_RSHIFT))
			m_tszText[m_iCnt++] = _T('D');
		else
			m_tszText[m_iCnt++] = _T('d');
	}

	if(CInputMgr::GetInstance()->KeyDown(DIK_E) && m_iCnt < 24)
	{
		if(CInputMgr::GetInstance()->KeyPress(DIK_LSHIFT) || CInputMgr::GetInstance()->KeyPress(DIK_RSHIFT))
			m_tszText[m_iCnt++] = _T('E');
		else
			m_tszText[m_iCnt++] = _T('e');
	}

	if(CInputMgr::GetInstance()->KeyDown(DIK_F) && m_iCnt < 24)
	{
		if(CInputMgr::GetInstance()->KeyPress(DIK_LSHIFT) || CInputMgr::GetInstance()->KeyPress(DIK_RSHIFT))
			m_tszText[m_iCnt++] = _T('F');
		else
			m_tszText[m_iCnt++] = _T('f');
	}

	if(CInputMgr::GetInstance()->KeyDown(DIK_G) && m_iCnt < 24)
	{
		if(CInputMgr::GetInstance()->KeyPress(DIK_LSHIFT) || CInputMgr::GetInstance()->KeyPress(DIK_RSHIFT))
			m_tszText[m_iCnt++] = _T('G');
		else
			m_tszText[m_iCnt++] = _T('g');
	}

	if(CInputMgr::GetInstance()->KeyDown(DIK_H) && m_iCnt < 24)
	{
		if(CInputMgr::GetInstance()->KeyPress(DIK_LSHIFT) || CInputMgr::GetInstance()->KeyPress(DIK_RSHIFT))
			m_tszText[m_iCnt++] = _T('H');
		else
			m_tszText[m_iCnt++] = _T('h');
	}

	if(CInputMgr::GetInstance()->KeyDown(DIK_I) && m_iCnt < 24)
	{
		if(CInputMgr::GetInstance()->KeyPress(DIK_LSHIFT) || CInputMgr::GetInstance()->KeyPress(DIK_RSHIFT))
			m_tszText[m_iCnt++] = _T('I');
		else
			m_tszText[m_iCnt++] = _T('i');
	}

	if(CInputMgr::GetInstance()->KeyDown(DIK_J) && m_iCnt < 24)
	{
		if(CInputMgr::GetInstance()->KeyPress(DIK_LSHIFT) || CInputMgr::GetInstance()->KeyPress(DIK_RSHIFT))
			m_tszText[m_iCnt++] = _T('J');
		else
			m_tszText[m_iCnt++] = _T('j');
	}

	if(CInputMgr::GetInstance()->KeyDown(DIK_K) && m_iCnt < 24)
	{
		if(CInputMgr::GetInstance()->KeyPress(DIK_LSHIFT) || CInputMgr::GetInstance()->KeyPress(DIK_RSHIFT))
			m_tszText[m_iCnt++] = _T('K');
		else
			m_tszText[m_iCnt++] = _T('k');
	}

	if(CInputMgr::GetInstance()->KeyDown(DIK_L) && m_iCnt < 24)
	{
		if(CInputMgr::GetInstance()->KeyPress(DIK_LSHIFT) || CInputMgr::GetInstance()->KeyPress(DIK_RSHIFT))
			m_tszText[m_iCnt++] = _T('L');
		else
			m_tszText[m_iCnt++] = _T('l');
	}

	if(CInputMgr::GetInstance()->KeyDown(DIK_M) && m_iCnt < 24)
	{
		if(CInputMgr::GetInstance()->KeyPress(DIK_LSHIFT) || CInputMgr::GetInstance()->KeyPress(DIK_RSHIFT))
			m_tszText[m_iCnt++] = _T('M');
		else
			m_tszText[m_iCnt++] = _T('m');
	}

	if(CInputMgr::GetInstance()->KeyDown(DIK_N) && m_iCnt < 24)
	{
		if(CInputMgr::GetInstance()->KeyPress(DIK_LSHIFT) || CInputMgr::GetInstance()->KeyPress(DIK_RSHIFT))
			m_tszText[m_iCnt++] = _T('N');
		else
			m_tszText[m_iCnt++] = _T('n');
	}

	if(CInputMgr::GetInstance()->KeyDown(DIK_O) && m_iCnt < 24)
	{
		if(CInputMgr::GetInstance()->KeyPress(DIK_LSHIFT) || CInputMgr::GetInstance()->KeyPress(DIK_RSHIFT))
			m_tszText[m_iCnt++] = _T('O');
		else
			m_tszText[m_iCnt++] = _T('o');
	}

	if(CInputMgr::GetInstance()->KeyDown(DIK_P) && m_iCnt < 24)
	{
		if(CInputMgr::GetInstance()->KeyPress(DIK_LSHIFT) || CInputMgr::GetInstance()->KeyPress(DIK_RSHIFT))
			m_tszText[m_iCnt++] = _T('P');
		else
			m_tszText[m_iCnt++] = _T('p');
	}

	if(CInputMgr::GetInstance()->KeyDown(DIK_Q) && m_iCnt < 24)
	{
		if(CInputMgr::GetInstance()->KeyPress(DIK_LSHIFT) || CInputMgr::GetInstance()->KeyPress(DIK_RSHIFT))
			m_tszText[m_iCnt++] = _T('Q');
		else
			m_tszText[m_iCnt++] = _T('q');
	}

	if(CInputMgr::GetInstance()->KeyDown(DIK_R) && m_iCnt < 24)
	{
		if(CInputMgr::GetInstance()->KeyPress(DIK_LSHIFT) || CInputMgr::GetInstance()->KeyPress(DIK_RSHIFT))
			m_tszText[m_iCnt++] = _T('R');
		else
			m_tszText[m_iCnt++] = _T('r');
	}

	if(CInputMgr::GetInstance()->KeyDown(DIK_S) && m_iCnt < 24)
	{
		if(CInputMgr::GetInstance()->KeyPress(DIK_LSHIFT) || CInputMgr::GetInstance()->KeyPress(DIK_RSHIFT))
			m_tszText[m_iCnt++] = _T('S');
		else
			m_tszText[m_iCnt++] = _T('s');
	}

	if(CInputMgr::GetInstance()->KeyDown(DIK_T) && m_iCnt < 24)
	{
		if(CInputMgr::GetInstance()->KeyPress(DIK_LSHIFT) || CInputMgr::GetInstance()->KeyPress(DIK_RSHIFT))
			m_tszText[m_iCnt++] = _T('T');
		else
			m_tszText[m_iCnt++] = _T('t');
	}

	if(CInputMgr::GetInstance()->KeyDown(DIK_U) && m_iCnt < 24)
	{
		if(CInputMgr::GetInstance()->KeyPress(DIK_LSHIFT) || CInputMgr::GetInstance()->KeyPress(DIK_RSHIFT))
			m_tszText[m_iCnt++] = _T('U');
		else
			m_tszText[m_iCnt++] = _T('u');
	}

	if(CInputMgr::GetInstance()->KeyDown(DIK_V) && m_iCnt < 24)
	{
		if(CInputMgr::GetInstance()->KeyPress(DIK_LSHIFT) || CInputMgr::GetInstance()->KeyPress(DIK_RSHIFT))
			m_tszText[m_iCnt++] = _T('V');
		else
			m_tszText[m_iCnt++] = _T('v');
	}

	if(CInputMgr::GetInstance()->KeyDown(DIK_W) && m_iCnt < 24)
	{
		if(CInputMgr::GetInstance()->KeyPress(DIK_LSHIFT) || CInputMgr::GetInstance()->KeyPress(DIK_RSHIFT))
			m_tszText[m_iCnt++] = _T('W');
		else
			m_tszText[m_iCnt++] = _T('w');
	}

	if(CInputMgr::GetInstance()->KeyDown(DIK_X) && m_iCnt < 24)
	{
		if(CInputMgr::GetInstance()->KeyPress(DIK_LSHIFT) || CInputMgr::GetInstance()->KeyPress(DIK_RSHIFT))
			m_tszText[m_iCnt++] = _T('X');
		else
			m_tszText[m_iCnt++] = _T('x');
	}

	if(CInputMgr::GetInstance()->KeyDown(DIK_Y) && m_iCnt < 24)
	{
		if(CInputMgr::GetInstance()->KeyPress(DIK_LSHIFT) || CInputMgr::GetInstance()->KeyPress(DIK_RSHIFT))
			m_tszText[m_iCnt++] = _T('Y');
		else
			m_tszText[m_iCnt++] = _T('y');
	}

	if(CInputMgr::GetInstance()->KeyDown(DIK_Z) && m_iCnt < 24)
	{
		if(CInputMgr::GetInstance()->KeyPress(DIK_LSHIFT) || CInputMgr::GetInstance()->KeyPress(DIK_RSHIFT))
			m_tszText[m_iCnt++] = _T('Z');
		else
			m_tszText[m_iCnt++] = _T('z');
	}

	return 0;
}

void CTextFieldUI::Render()
{
	CUI::Render();

	if(m_dwState & UI_OVER)
		m_pMaterialCom->m_pTexture = m_pOverTexture;
}

void CTextFieldUI::Release()
{
}