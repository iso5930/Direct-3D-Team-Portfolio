#include "StdAfx.h"
#include "DetailMessage.h"

CDetailMessage::CDetailMessage(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, TCHAR* _tszText)
: CMessageUI(_tszObjKey, _eObjType, _T("Message_Interface"))
{
	// Text
	_tcscpy_s(m_tszText, MAX_STR, _tszText);

	// CalcRect
	RECT rcText;
	CFontMgr::GetInstance()->GetBauhaus(12, 5)->DrawText(NULL, m_tszText, -1, &rcText, DT_CALCRECT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	// Width
	m_iWidth = rcText.right - rcText.left;

	// Height
	m_iHeight = rcText.bottom - rcText.top;

	// Size
	m_pTransformCom->m_vSize.x = m_iWidth / float(WINCX) * 2.0f + 0.04f;
	m_pTransformCom->m_vSize.y = m_iHeight / float(WINCY) * 2.0f + 0.03f;
	m_pTransformCom->m_vSize.z = 0.0f;
}

CDetailMessage::~CDetailMessage()
{
	Release();
}

void CDetailMessage::Initialize()
{
	CMessageUI::Initialize();
}

int CDetailMessage::Update()
{
	CMessageUI::Update();

	return 0;
}

void CDetailMessage::Render()
{
	CMessageUI::Render();

	D3DXVECTOR3 vPos;
	ProjToScreen(&vPos, &m_pTransformCom->m_vPos);

	RECT rcText;
	SetRect(&rcText, long(vPos.x - m_iWidth / 2.0f), long(vPos.y - m_iHeight / 2.0f), long(vPos.x + m_iWidth / 2.0f), long(vPos.y + m_iHeight / 2.0f));
	CFontMgr::GetInstance()->GetBauhaus(12, 5)->DrawText(NULL, m_tszText, -1, &rcText, DT_CENTER, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
}

void CDetailMessage::Release()
{
}