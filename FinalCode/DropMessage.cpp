#include "StdAfx.h"
#include "DropMessage.h"

CDropMessage::CDropMessage(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, Item* _pItem)
: CMessageUI(_tszObjKey, _eObjType, _T("Message_Interface"))
{
	// Text
	_tcscpy_s(m_tszText, MAX_STR, _pItem->tszName);

	// CalcRect
	RECT rcText;
	CFontMgr::GetInstance()->GetBauhaus(16, 8)->DrawText(NULL, m_tszText, -1, &rcText, DT_CALCRECT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	// Width
	m_iWidth = rcText.right - rcText.left;

	// Height
	m_iHeight = rcText.bottom - rcText.top;

	// Color
	if(_pItem->dwItemClass == 0)
		m_dwColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	else if(_pItem->dwItemClass & ITEM_CLASS_NORMAL)
		m_dwColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	else if(_pItem->dwItemClass & ITEM_CLASS_MAGIC)
		m_dwColor = D3DXCOLOR(0.368627f, 0.37647f, 0.803921f, 1.0f);
	else if(_pItem->dwItemClass & ITEM_CLASS_UNIQUE)
		m_dwColor = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
	else if(_pItem->dwItemClass & ITEM_CLASS_LEGEND)
		m_dwColor = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	else if(_pItem->dwItemClass & ITEM_CLASS_SET)
		m_dwColor = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);

	// Size
	m_pTransformCom->m_vSize.x = m_iWidth / float(WINCX) * 2.0f + 0.04f;
	m_pTransformCom->m_vSize.y = m_iHeight / float(WINCY) * 4.0f + 0.01f;
}

CDropMessage::~CDropMessage()
{
	Release();
}

void CDropMessage::Initialize()
{
	CMessageUI::Initialize();
}

int CDropMessage::Update()
{
	CMessageUI::Update();

	return 0;
}

void CDropMessage::Render()
{
	CMessageUI::Render();

	D3DXVECTOR3 vPos;
	ProjToScreen(&vPos, &m_pTransformCom->m_vPos);

	RECT rcText;
	SetRect(&rcText, long(vPos.x - m_iWidth / 2.0f), long(vPos.y - m_iHeight / 2.0f), long(vPos.x + m_iWidth / 2.0f), long(vPos.y + m_iHeight / 2.0f));
	CFontMgr::GetInstance()->GetBauhaus(16, 8)->DrawText(NULL, m_tszText, -1, &rcText, DT_CENTER, m_dwColor);
}

void CDropMessage::Release()
{
}