#include "StdAfx.h"
#include "StoreSign.h"

CStoreSign::CStoreSign(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, Item* _pItem)
: CSignUI(_tszObjKey, _eObjType, _T("Sign_Store"))
{
	// Item
	m_pItem = new Item(_pItem);

	// Sign
	m_pSign = NULL;

	// GridSign
	m_pGridSign = NULL;
	
	// ItemMessage
	m_pItemMessage = NULL;

	// Size
	m_pTransformCom->m_vSize = D3DXVECTOR3(0.229f, 0.216f, 0.0f);
}

CStoreSign::~CStoreSign()
{
	Release();
}

void CStoreSign::Initialize()
{
	CSignUI::Initialize();

	CUpdateCom* pUpdateCom = (CUpdateCom*)m_pComponent[COM_TYPE_UPDATE];
	if(pUpdateCom != NULL)
		pUpdateCom->m_dwPriority = 0xFFFFFFF6;

	CRenderCom* pRenderCom = (CRenderCom*)m_pComponent[COM_TYPE_RENDER];
	if(pRenderCom != NULL)
		pRenderCom->m_dwPriority = 0x00000009;

	CTransformCom* pTransformCom;

	// Sign
	m_pSign = new CBasicSign(NULL, OBJ_TYPE_STATIC, m_pItem->tszTexKey);
	m_pLayer->AddObject(m_pSign, LAYER_TYPE_UI);

	pTransformCom = (CTransformCom*)m_pSign->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = m_pTransformCom->m_vPos - D3DXVECTOR3(0.0859967f, -0.00499615f, 0.0f);
	pTransformCom->m_vSize = D3DXVECTOR3(0.047f, 0.1f * m_pItem->iHeight, 0.0f);

	m_pSign->Initialize();

	// GridSign
	if(m_pItem->dwItemClass & ITEM_CLASS_MAGIC)
		m_pGridSign = new CStoreGridSign(NULL, OBJ_TYPE_STATIC, _T("Sign_MagicGrid"));
	else if(m_pItem->dwItemClass & ITEM_CLASS_UNIQUE)
		m_pGridSign = new CStoreGridSign(NULL, OBJ_TYPE_STATIC, _T("Sign_UniqueGrid"));
	else if(m_pItem->dwItemClass & ITEM_CLASS_LEGEND)
		m_pGridSign = new CStoreGridSign(NULL, OBJ_TYPE_STATIC, _T("Sign_LegendGrid"));
	else if(m_pItem->dwItemClass & ITEM_CLASS_SET)
		m_pGridSign = new CStoreGridSign(NULL, OBJ_TYPE_STATIC, _T("Sign_SetGrid"));

	if(m_pGridSign != NULL)
	{
		m_pLayer->AddObject(m_pGridSign, LAYER_TYPE_UI);

		pTransformCom = (CTransformCom*)m_pGridSign->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = m_pTransformCom->m_vPos - D3DXVECTOR3(0.0859967f, -0.00499615f, 0.0f);

		m_pGridSign->Initialize();
	}
}

int CStoreSign::Update()
{
	CSignUI::Update();

	CUpdateCom* pUpdateCom = (CUpdateCom*)m_pComponent[COM_TYPE_UPDATE];
	if(pUpdateCom != NULL)
		pUpdateCom->m_dwPriority = 0xFFFFFFF6;

	CRenderCom* pRenderCom = (CRenderCom*)m_pComponent[COM_TYPE_RENDER];
	if(pRenderCom != NULL)
		pRenderCom->m_dwPriority = 0x00000009;

	return 0;
}

void CStoreSign::Render()
{
	CSignUI::Render();

	D3DXVECTOR3 vPos;
	ProjToScreen(&vPos, &D3DXVECTOR3(m_pTransformCom->m_vPos.x, m_pTransformCom->m_vPos.y + m_pTransformCom->m_vSize.y / 2.0f, 0.0f));

	TCHAR tszTemp0[MIN_STR], tszTemp1[MIN_STR];
	ZeroMemory(tszTemp0, sizeof(tszTemp0));
	ZeroMemory(tszTemp1, sizeof(tszTemp1));

	int iLen = _tcslen(m_pItem->tszName);
	for(int i = 0; i < iLen; ++i)
	{
		if(i < 6)
			tszTemp0[i] = m_pItem->tszName[i];
		else
			tszTemp1[i - 6] = m_pItem->tszName[i];
	}

	RECT rcText;
	SetRect(&rcText, long(vPos.x - 28.0f), long(vPos.y + 16.0f), long(vPos.x + 54.0f), long(vPos.y + 30.0f));
	CFontMgr::GetInstance()->GetBauhaus(14, 7)->DrawText(NULL, tszTemp0, -1, &rcText, DT_LEFT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	SetRect(&rcText, long(vPos.x - 28.0f), long(vPos.y + 33.0f), long(vPos.x + 54.0f), long(vPos.y + 47.0f));
	CFontMgr::GetInstance()->GetBauhaus(14, 7)->DrawText(NULL, tszTemp1, -1, &rcText, DT_LEFT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	// Value
	TCHAR tszValue[MIN_STR];
	_itot_s(m_pItem->iValue * m_pItem->iNum, tszValue, 10);

	SetRect(&rcText, long(vPos.x - 28.0f), long(vPos.y + 61.0f), long(vPos.x + 54.0f), long(vPos.y + 73.0f));
	CFontMgr::GetInstance()->GetBauhaus(12, 6)->DrawText(NULL, tszValue, -1, &rcText, DT_RIGHT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	if(m_pItem->dwItemType & (ITEM_TYPE_GEM |ITEM_TYPE_MATERIAL))
	{
		TCHAR tszNum[MIN_STR];
		_itot_s(m_pItem->iNum, tszNum, 10);

		RECT rcText;
		SetRect(&rcText, long(vPos.x - 142.0f), long(vPos.y + 61.0f), long(vPos.x - 42.0f), long(vPos.y + 75.0f));
		CFontMgr::GetInstance()->GetBauhaus(12, 6)->DrawText(NULL, tszNum, -1, &rcText, DT_RIGHT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
}

void CStoreSign::Release()
{
	// Item
	if(m_pItem != NULL)
	{
		delete m_pItem;
		m_pItem = NULL;
	}

	// Sign
	if(m_pSign != NULL)
	{
		m_pSign->Destroy();
		m_pSign = NULL;
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
}

void CStoreSign::EnableItemMessage()
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

void CStoreSign::DisableItemMessage()
{
	if(m_pItemMessage == NULL)
		return;

	m_pItemMessage->Destroy();
	m_pItemMessage = NULL;
}