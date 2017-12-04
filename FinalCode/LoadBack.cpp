#include "StdAfx.h"
#include "LoadBack.h"

CLoadBack::CLoadBack(TCHAR* _tszObjKey, OBJ_TYPE _eObjType)
: CBack(_tszObjKey, _eObjType, _T("Back_Load"))
{
	// Time
	m_fTime = 0.0f;

	// Dot
	m_iDot = 0;

	// Text
	ZeroMemory(m_tszText, sizeof(m_tszText));
}

CLoadBack::~CLoadBack()
{
	Release();
}

void CLoadBack::Initialize()
{
	CBack::Initialize();
}

int CLoadBack::Update()
{
	CBack::Update();

	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();
	if(m_fTime > 0.5f)
	{
		m_fTime = 0.0f;
		if(++m_iDot > 3)
			m_iDot = 0;
	}

	return 0;
}

void CLoadBack::Render()
{
	CBack::Render();

	// Text
	_tcscpy_s(m_tszText, MAX_STR, _T("Loading"));

	// Dot
	for(int i = 0; i < m_iDot; ++i)
		_tcscat_s(m_tszText, MAX_STR, _T("."));

	RECT rcText;
	SetRect(&rcText, 0, 565, WINCX, WINCY);
	CFontMgr::GetInstance()->GetBauhaus(16, 8)->DrawText(NULL, m_tszText, -1, &rcText, DT_CENTER, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
}

void CLoadBack::Release()
{
}