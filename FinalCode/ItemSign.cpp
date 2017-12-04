#include "StdAfx.h"
#include "ItemSign.h"

CItemSign::CItemSign(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, Item* _pItem)
: CSignUI(_tszObjKey, _eObjType, _pItem->tszTexKey)
{
	// Item
	m_pItem = new Item(_pItem);

	// GridSign
	m_pGridSign = NULL;

	// ItemMessage
	m_pItemMessage = NULL;

	// ItemPannelSign
	m_pItemPannelSign = NULL;

	// SockSign
	ZeroMemory(m_pSockSign, sizeof(m_pSockSign));
}

CItemSign::~CItemSign()
{
	Release();
}

void CItemSign::Initialize()
{
	CSignUI::Initialize();

	CUpdateCom* pUpdateCom = (CUpdateCom*)m_pComponent[COM_TYPE_UPDATE];
	if(pUpdateCom != NULL)
		pUpdateCom->m_dwPriority = 0xFFFFFFF7;

	CRenderCom* pRenderCom = (CRenderCom*)m_pComponent[COM_TYPE_RENDER];
	if(pRenderCom != NULL)
		pRenderCom->m_dwPriority = 0x00000008;
}

int CItemSign::Update()
{
	CSignUI::Update();

	/*
	CUpdateCom* pUpdateCom = (CUpdateCom*)m_pComponent[COM_TYPE_UPDATE];
	if(pUpdateCom != NULL)
		pUpdateCom->m_dwPriority = 0xFFFFFFF7;

	CRenderCom* pRenderCom = (CRenderCom*)m_pComponent[COM_TYPE_RENDER];
	if(pRenderCom != NULL)
		pRenderCom->m_dwPriority = 0x00000008;
	*/

	return 0;
}

void CItemSign::Render()
{
	CSignUI::Render();

	D3DXVECTOR3 vPos;
	ProjToScreen(&vPos, &m_pTransformCom->m_vPos);

	if(m_pItem->dwItemType & (ITEM_TYPE_GEM |ITEM_TYPE_MATERIAL))
	{
		TCHAR tszNum[MIN_STR];
		_itot_s(m_pItem->iNum, tszNum, 10);

		RECT rcText;
		SetRect(&rcText, long(vPos.x - 15.0f), long(vPos.y + 2.0f), long(vPos.x + 15.0f), long(vPos.y + 14.0f));
		CFontMgr::GetInstance()->GetBauhaus(12, 6)->DrawText(NULL, tszNum, -1, &rcText, DT_RIGHT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
}

void CItemSign::Release()
{
	// Item
	if(m_pItem != NULL)
	{
		delete m_pItem;
		m_pItem = NULL;
	}

	// GridSign
	if(m_pGridSign != NULL)
	{
		m_pGridSign->Destroy();
		m_pGridSign = NULL;
	}

	// ItemMessage
	if(m_pItemMessage != NULL)
	{
		m_pItemMessage->Destroy();
		m_pItemMessage = NULL;
	}

	// ItemPannelSign
	if(m_pItemPannelSign != NULL)
	{
		m_pItemPannelSign->Destroy();
		m_pItemPannelSign = NULL;
	}

	// SockSign
	for(int i = 0; i < 3; ++i)
	{
		if(m_pSockSign[i] != NULL)
		{
			m_pSockSign[i]->Destroy();
			m_pSockSign[i] = NULL;
		}
	}
}

void CItemSign::EnableGridSign()
{
	if(m_pGridSign != NULL)
		return;

	if(m_pItem->dwItemClass & ITEM_CLASS_MAGIC)
		m_pGridSign = new CGridSign(NULL, OBJ_TYPE_STATIC, _T("Sign_MagicGrid"));
	else if(m_pItem->dwItemClass & ITEM_CLASS_UNIQUE)
		m_pGridSign = new CGridSign(NULL, OBJ_TYPE_STATIC, _T("Sign_UniqueGrid"));
	else if(m_pItem->dwItemClass & ITEM_CLASS_LEGEND)
		m_pGridSign = new CGridSign(NULL, OBJ_TYPE_STATIC, _T("Sign_LegendGrid"));
	else if(m_pItem->dwItemClass & ITEM_CLASS_SET)
		m_pGridSign = new CGridSign(NULL, OBJ_TYPE_STATIC, _T("Sign_SetGrid"));

	if(m_pGridSign == NULL)
		return;

	m_pLayer->AddObject(m_pGridSign, LAYER_TYPE_UI);

	CTransformCom* pTransformCom = (CTransformCom*)m_pGridSign->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = m_pTransformCom->m_vPos;
	pTransformCom->m_vSize = m_pTransformCom->m_vSize;
	m_pGridSign->Initialize();
}

void CItemSign::DisableGridSign()
{
	if(m_pGridSign == NULL)
		return;

	m_pGridSign->Destroy();
	m_pGridSign = NULL;
}

void CItemSign::EnableItemMessage()
{
	if(m_pItemMessage != NULL)
		return;

	m_pItemMessage = new CItemMessage(NULL, OBJ_TYPE_STATIC, m_pItem);
	m_pLayer->AddObject(m_pItemMessage, LAYER_TYPE_UI);

	if(m_pTransformCom->m_vPos.x > 0.0f)
	{
		CTransformCom* pTransformCom = (CTransformCom*)m_pItemMessage->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos.x = m_pTransformCom->m_vPos.x - m_pTransformCom->m_vSize.x / 2.0f - 0.01f;
		pTransformCom->m_vPos.y = m_pTransformCom->m_vPos.y;
	}
	else
	{
		CTransformCom* pTransformCom = (CTransformCom*)m_pItemMessage->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos.x = m_pTransformCom->m_vPos.x + m_pTransformCom->m_vSize.x / 2.0f + 0.01f + 0.4166f;
		pTransformCom->m_vPos.y = m_pTransformCom->m_vPos.y;
	}

	m_pItemMessage->Initialize();
}

void CItemSign::DisableItemMessage()
{
	if(m_pItemMessage == NULL)
		return;
	
	m_pItemMessage->Destroy();
	m_pItemMessage = NULL;
}

void CItemSign::EnableItemPannelSign()
{
	if(m_pItemPannelSign != NULL)
		return;

	m_pItemPannelSign = new CItemPannelSign(NULL, OBJ_TYPE_STATIC);
	m_pLayer->AddObject(m_pItemPannelSign, LAYER_TYPE_UI);

	CTransformCom* pTransformCom = (CTransformCom*)m_pItemPannelSign->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = m_pTransformCom->m_vPos;
	pTransformCom->m_vSize = m_pTransformCom->m_vSize + D3DXVECTOR3(0.005f, 0.005f, 0.0f);
	m_pItemPannelSign->Initialize();
}

void CItemSign::DisableItemPannelSign()
{
	if(m_pItemPannelSign == NULL)
		return;

	m_pItemPannelSign->Destroy();
	m_pItemPannelSign = NULL;
}

void CItemSign::EnableSockSign()
{
	// SockSign
	for(int i = 0; i < m_pItem->iSockNum; ++i)
	{
		if(m_pSockSign[i] != NULL)
			continue;

		m_pSockSign[i] = new CSockSign(NULL, OBJ_TYPE_STATIC, m_pItem->SockArr[i]);
		m_pLayer->AddObject(m_pSockSign[i], LAYER_TYPE_UI);

		// Pos
		CTransformCom* pTransformCom = (CTransformCom*)m_pSockSign[i]->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos.x = m_pTransformCom->m_vPos.x;
		pTransformCom->m_vPos.y = m_pTransformCom->m_vPos.y + m_pTransformCom->m_vSize.y / 6.0f * (m_pItem->iSockNum - 1) - m_pTransformCom->m_vSize.y / 6.0f * i * 2.0f;

		// Size
		pTransformCom->m_vSize = D3DXVECTOR3(0.04f, 0.06f, 0.0f);

		// UpdateCom
		CUpdateCom* pUpdateCom = (CUpdateCom*)m_pSockSign[i]->GetComponent(COM_TYPE_UPDATE);
		if(pUpdateCom != NULL)
			pUpdateCom->m_dwPriority = 0xFFFFFFF8;

		// RenderCom
		CRenderCom* pRenderCom = (CRenderCom*)m_pSockSign[i]->GetComponent(COM_TYPE_RENDER);
		if(pRenderCom != NULL)
			pRenderCom->m_dwPriority = 0x00000007;

		m_pSockSign[i]->Initialize();
	}
}

void CItemSign::DisableSockSign()
{
	for(int i = 0; i < m_pItem->iSockNum; ++i)
	{
		if(m_pSockSign[i] == NULL)
			continue;

		m_pSockSign[i]->Destroy();
		m_pSockSign[i] = NULL;
	}
}