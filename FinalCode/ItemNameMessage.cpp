#include "StdAfx.h"
#include "ItemNameMessage.h"

CItemNameMessage::CItemNameMessage(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, Item* _pItem)
: CMessageUI(_tszObjKey, _eObjType, NULL)
{
	// Item
	m_pItem = new Item(_pItem);

	// Text
	_tcscpy_s(m_tszText, MIN_STR, _pItem->tszName);

	if(m_pItem->dwItemType & (ITEM_TYPE_GEM | ITEM_TYPE_MATERIAL))
	{
		TCHAR tszNum[MIN_STR];
		_itot_s(m_pItem->iNum, tszNum, 10);
		
		_tcscat_s(m_tszText, MIN_STR, _T("("));
		_tcscat_s(m_tszText, MIN_STR, tszNum);
		_tcscat_s(m_tszText, MIN_STR, _T(")"));
	}

	m_dwColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_ItemNameNormal"));
	if(_pItem->dwItemClass & ITEM_CLASS_NORMAL)
	{
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_ItemNameNormal"));
		m_dwColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}
	else if(_pItem->dwItemClass & ITEM_CLASS_MAGIC)
	{
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_ItemNameMagic"));
		m_dwColor = D3DXCOLOR(0.368627f, 0.37647f, 0.803921f, 1.0f);
	}
	else if(_pItem->dwItemClass & ITEM_CLASS_UNIQUE)
	{
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_ItemNameUnique"));
		m_dwColor = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
	}
	else if(_pItem->dwItemClass & ITEM_CLASS_LEGEND)
	{
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_ItemNameLegend"));
		m_dwColor = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	}
	else if(_pItem->dwItemClass & ITEM_CLASS_SET)
	{
		m_pBackTexture = CTextureMgr::GetInstance()->GetTexture(_T("Message_ItemNameSet"));
		m_dwColor = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
	}
}

CItemNameMessage::~CItemNameMessage()
{
	Release();
}

void CItemNameMessage::Initialize()
{
	CMessageUI::Initialize();

	CUpdateCom* pUpdateCom = (CUpdateCom*)m_pComponent[COM_TYPE_UPDATE];
	if(pUpdateCom != NULL)
		pUpdateCom->m_dwPriority = 0xFFFFFFFA;

	CRenderCom* pRenderCom = (CRenderCom*)m_pComponent[COM_TYPE_RENDER];
	if(pRenderCom != NULL)
		pRenderCom->m_dwPriority = 0x00000005;
}

int CItemNameMessage::Update()
{
	CMessageUI::Update();

	CUpdateCom* pUpdateCom = (CUpdateCom*)m_pComponent[COM_TYPE_UPDATE];
	if(pUpdateCom != NULL)
		pUpdateCom->m_dwPriority = 0xFFFFFFFA;

	CRenderCom* pRenderCom = (CRenderCom*)m_pComponent[COM_TYPE_RENDER];
	if(pRenderCom != NULL)
		pRenderCom->m_dwPriority = 0x00000005;

	return 0;
}

void CItemNameMessage::Render()
{
	CMessageUI::Render();

	D3DXVECTOR3 vPos;
	ProjToScreen(&vPos, &m_pTransformCom->m_vPos);

	RECT rcText;
	SetRect(&rcText, long(vPos.x - 120), long(vPos.y - 7), long(vPos.x + 120), long(vPos.y + 9));
	CFontMgr::GetInstance()->GetBauhaus(16, 8)->DrawText(NULL, m_tszText, -1, &rcText, DT_CENTER, m_dwColor);
}

void CItemNameMessage::Release()
{
	// Item
	if(m_pItem != NULL)
	{
		delete m_pItem;
		m_pItem = NULL;
	}
}