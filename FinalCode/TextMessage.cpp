#include "StdAfx.h"
#include "TextMessage.h"

CTextMessage::CTextMessage(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, TCHAR* _tszText)
: CMessageUI(_tszObjKey, _eObjType, _T("Message_Alpha"))
{
	// Time
	m_fTime = 0.0f;

	// Alpha
	m_fAlpha = 1.0f;

	// Mode
	m_iMode = 0;

	// Text
	_tcscpy_s(m_tszText, MIN_STR, _tszText);

	// Size
	m_pTransformCom->m_vSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

CTextMessage::~CTextMessage()
{
	Release();
}

void CTextMessage::Initialize()
{
	CMessageUI::Initialize();
}

int CTextMessage::Update()
{
	CMessageUI::Update();

	switch(m_iMode)
	{
	case 0:
		Mode0();
		break;

	case 1:
		Mode1();
		break;

	case 2:
		Mode2();
		break;
	}
	return 0;
}

void CTextMessage::Render()
{
	CMessageUI::Render();

	RECT rcText;
	SetRect(&rcText, 0, 50, WINCX, WINCY);
	CFontMgr::GetInstance()->GetBauhaus(20, 8)->DrawText(NULL, m_tszText, -1, &rcText, DT_CENTER, D3DXCOLOR(0.8313f, 0.0705f, 0.0705f, m_fAlpha));
}

void CTextMessage::Release()
{
}

void CTextMessage::Mode0()
{
	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();
	if(m_fTime > 1.0f)
	{
		m_fTime = 0.0f;
		++m_iMode;
	}
}

void CTextMessage::Mode1()
{
	m_fAlpha -= CTimeMgr::GetInstance()->GetDeltaTime() / 2.0f;
	if(m_fAlpha < 0.0f)
		m_fAlpha = 0.0f;

	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();
	if(m_fTime > 2.0f)
	{
		m_fTime = 0.0f;
		++m_iMode;
	}
}

void CTextMessage::Mode2()
{
	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();
	if(m_fTime > 1.0f)
		Destroy();
}