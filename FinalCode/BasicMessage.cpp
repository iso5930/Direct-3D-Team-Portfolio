#include "StdAfx.h"
#include "BasicMessage.h"

CBasicMessage::CBasicMessage(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, TCHAR* _tszBackTexKey, TCHAR* _tszText)
: CMessageUI(_tszObjKey, _eObjType, _tszBackTexKey)
{
	// Text
	_tcscpy_s(m_tszText, MAX_STR, _tszText);

	// CalcRect
	RECT rcText;
	CFontMgr::GetInstance()->GetBauhaus(16, 8)->DrawText(NULL, m_tszText, -1, &rcText, DT_CALCRECT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	// Width
	m_iWidth = rcText.right - rcText.left;

	// Height
	m_iHeight = rcText.bottom - rcText.top;

	// Size
	m_pTransformCom->m_vSize.x = m_iWidth / float(WINCX) * 2.0f + 0.04f;
	m_pTransformCom->m_vSize.y = m_iHeight / float(WINCY) * 4.0f + 0.01f;
}

CBasicMessage::~CBasicMessage()
{
	Release();
}

void CBasicMessage::Initialize()
{
	CMessageUI::Initialize();
}

int CBasicMessage::Update()
{
	CMessageUI::Update();

	return 0;
}

void CBasicMessage::Render()
{
	CMessageUI::Render();

	D3DXVECTOR3 vPos;
	ProjToScreen(&vPos, &m_pTransformCom->m_vPos);

	RECT rcText;
	SetRect(&rcText, long(vPos.x - m_iWidth / 2.0f), long(vPos.y - m_iHeight / 2.0f), long(vPos.x + m_iWidth / 2.0f), long(vPos.y + m_iHeight / 2.0f));
	CFontMgr::GetInstance()->GetBauhaus(16, 8)->DrawText(NULL, m_tszText, -1, &rcText, DT_CENTER, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
}

void CBasicMessage::Release()
{
}