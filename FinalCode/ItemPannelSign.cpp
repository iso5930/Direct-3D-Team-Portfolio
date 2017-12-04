#include "StdAfx.h"
#include "ItemPannelSign.h"

CItemPannelSign::CItemPannelSign(TCHAR* _tszObjKey, OBJ_TYPE _eObjType)
: CSignUI(_tszObjKey, _eObjType, _T("Sign_ItemPannel"))
{
}

CItemPannelSign::~CItemPannelSign()
{
	Release();
}

void CItemPannelSign::Initialize()
{
	CSignUI::Initialize();

	CUpdateCom* pUpdateCom = (CUpdateCom*)m_pComponent[COM_TYPE_UPDATE];
	if(pUpdateCom != NULL)
		pUpdateCom->m_dwPriority = 0xFFFFFFF6;

	CRenderCom* pRenderCom = (CRenderCom*)m_pComponent[COM_TYPE_RENDER];
	if(pRenderCom != NULL)
		pRenderCom->m_dwPriority = 0x00000009;
}

int CItemPannelSign::Update()
{
	CSignUI::Update();

	return 0;
}

void CItemPannelSign::Render()
{
	CSignUI::Render();
}

void CItemPannelSign::Release()
{
}