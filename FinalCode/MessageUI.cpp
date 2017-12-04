#include "StdAfx.h"
#include "MessageUI.h"

CMessageUI::CMessageUI(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, TCHAR* _tszBackTexKey)
: CUI(_tszObjKey, _eObjType, _tszBackTexKey)
{
	// Text
	ZeroMemory(m_tszText, sizeof(m_tszText));

	// CloseButton
	m_pCloseButton = NULL;
}

CMessageUI::~CMessageUI()
{
	Release();
}

void CMessageUI::Initialize()
{
	CUI::Initialize();
}

int CMessageUI::Update()
{
	CUI::Update();

	CUpdateCom* pUpdateCom = (CUpdateCom*)m_pComponent[COM_TYPE_UPDATE];
	if(pUpdateCom != NULL)
		pUpdateCom->m_dwPriority = 0xFFFFFFFA;

	CRenderCom* pRenderCom = (CRenderCom*)m_pComponent[COM_TYPE_RENDER];
	if(pRenderCom != NULL)
		pRenderCom->m_dwPriority = 0x00000005;

	if(m_pCloseButton != NULL)
	{
		pUpdateCom = (CUpdateCom*)m_pCloseButton->GetComponent(COM_TYPE_UPDATE);
		if(pUpdateCom != NULL)
			pUpdateCom->m_dwPriority = 0xFFFFFFFB;

		pRenderCom = (CRenderCom*)m_pCloseButton->GetComponent(COM_TYPE_RENDER);
		if(pRenderCom != NULL)
			pRenderCom->m_dwPriority = 0x00000004;

		if(m_pCloseButton->IsLUp())
			Destroy();
	}

	return 0;
}

void CMessageUI::Render()
{
	CUI::Render();
}

void CMessageUI::Release()
{
	// CloseButton
	if(m_pCloseButton != NULL)
	{
		m_pCloseButton->Destroy();
		m_pCloseButton = NULL;
	}
}
