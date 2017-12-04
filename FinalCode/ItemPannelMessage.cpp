#include "StdAfx.h"
#include "ItemPannelMessage.h"

CItemPannelMessage::CItemPannelMessage(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, TCHAR* _tszBackTexKey)
: CMessageUI(_tszObjKey, _eObjType, _tszBackTexKey)
{
}

CItemPannelMessage::~CItemPannelMessage()
{
	Release();
}

void CItemPannelMessage::Initialize()
{
	CMessageUI::Initialize();

	CUpdateCom* pUpdateCom = (CUpdateCom*)m_pComponent[COM_TYPE_UPDATE];
	if(pUpdateCom != NULL)
		pUpdateCom->m_dwPriority = 0xFFFFFFFB;

	CRenderCom* pRenderCom = (CRenderCom*)m_pComponent[COM_TYPE_RENDER];
	if(pRenderCom != NULL)
		pRenderCom->m_dwPriority = 0x00000004;
}

int CItemPannelMessage::Update()
{
	CMessageUI::Update();

	CUpdateCom* pUpdateCom = (CUpdateCom*)m_pComponent[COM_TYPE_UPDATE];
	if(pUpdateCom != NULL)
		pUpdateCom->m_dwPriority = 0xFFFFFFFB;

	CRenderCom* pRenderCom = (CRenderCom*)m_pComponent[COM_TYPE_RENDER];
	if(pRenderCom != NULL)
		pRenderCom->m_dwPriority = 0x00000004;

	return 0;
}

void CItemPannelMessage::Render()
{
	CMessageUI::Render();
}

void CItemPannelMessage::Release()
{
}