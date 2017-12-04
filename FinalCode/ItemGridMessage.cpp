#include "StdAfx.h"
#include "ItemGridMessage.h"

CItemGridMessage::CItemGridMessage(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, TCHAR* _tszBackTexKey)
: CMessageUI(_tszObjKey, _eObjType, _tszBackTexKey)
{
}

CItemGridMessage::~CItemGridMessage()
{
	Release();
}

void CItemGridMessage::Initialize()
{
	CMessageUI::Initialize();

	CUpdateCom* pUpdateCom = (CUpdateCom*)m_pComponent[COM_TYPE_UPDATE];
	if(pUpdateCom != NULL)
		pUpdateCom->m_dwPriority = 0xFFFFFFFC;

	CRenderCom* pRenderCom = (CRenderCom*)m_pComponent[COM_TYPE_RENDER];
	if(pRenderCom != NULL)
		pRenderCom->m_dwPriority = 0x00000003;
}

int CItemGridMessage::Update()
{
	CMessageUI::Update();

	CUpdateCom* pUpdateCom = (CUpdateCom*)m_pComponent[COM_TYPE_UPDATE];
	if(pUpdateCom != NULL)
		pUpdateCom->m_dwPriority = 0xFFFFFFFC;

	CRenderCom* pRenderCom = (CRenderCom*)m_pComponent[COM_TYPE_RENDER];
	if(pRenderCom != NULL)
		pRenderCom->m_dwPriority = 0x00000003;

	return 0;
}

void CItemGridMessage::Render()
{
	CMessageUI::Render();
}

void CItemGridMessage::Release()
{
}