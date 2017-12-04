#include "StdAfx.h"
#include "ItemIconMessage.h"

CItemIconMessage::CItemIconMessage(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, TCHAR* _tszBackTexKey)
: CMessageUI(_tszObjKey, _eObjType, _tszBackTexKey)
{
}

CItemIconMessage::~CItemIconMessage()
{
	Release();
}

void CItemIconMessage::Initialize()
{
	CMessageUI::Initialize();

	CUpdateCom* pUpdateCom = (CUpdateCom*)m_pComponent[COM_TYPE_UPDATE];
	if(pUpdateCom != NULL)
		pUpdateCom->m_dwPriority = 0xFFFFFFFD;

	CRenderCom* pRenderCom = (CRenderCom*)m_pComponent[COM_TYPE_RENDER];
	if(pRenderCom != NULL)
		pRenderCom->m_dwPriority = 0x00000002;
}

int CItemIconMessage::Update()
{
	CMessageUI::Update();

	CUpdateCom* pUpdateCom = (CUpdateCom*)m_pComponent[COM_TYPE_UPDATE];
	if(pUpdateCom != NULL)
		pUpdateCom->m_dwPriority = 0xFFFFFFFD;

	CRenderCom* pRenderCom = (CRenderCom*)m_pComponent[COM_TYPE_RENDER];
	if(pRenderCom != NULL)
		pRenderCom->m_dwPriority = 0x00000002;

	return 0;
}

void CItemIconMessage::Render()
{
	CMessageUI::Render();
}

void CItemIconMessage::Release()
{
}