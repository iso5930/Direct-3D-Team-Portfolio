#include "StdAfx.h"
#include "WindowUI.h"

CWindowUI::CWindowUI(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, TCHAR* _tszBackTexKey)
: CUI(_tszObjKey, _eObjType, _tszBackTexKey)
{
}

CWindowUI::~CWindowUI()
{
	Release();
}

void CWindowUI::Initialize()
{
	CUI::Initialize();
}

int CWindowUI::Update()
{
	CUI::Update();

	if(m_dwState & UI_OVER)
	{
		CInputMgr::GetInstance()->MousePosInvalidate();
		CInputMgr::GetInstance()->MouseInvalidate();
	}

	CUpdateCom* pUpdateCom = (CUpdateCom*)m_pComponent[COM_TYPE_UPDATE];
	if(pUpdateCom != NULL)
		pUpdateCom->m_dwPriority = 0xFFFFFFF5;

	CRenderCom* pRenderCom = (CRenderCom*)m_pComponent[COM_TYPE_RENDER];
	if(pRenderCom != NULL)
		pRenderCom->m_dwPriority = 0x0000000A;

	for(size_t i = 0; i < m_ButtonVec.size(); ++i)
	{
		pUpdateCom = (CUpdateCom*)m_ButtonVec[i]->GetComponent(COM_TYPE_UPDATE);
		if(pUpdateCom != NULL)
			pUpdateCom->m_dwPriority = 0xFFFFFFF6;

		pRenderCom = (CRenderCom*)m_ButtonVec[i]->GetComponent(COM_TYPE_RENDER);
		if(pRenderCom != NULL)
			pRenderCom->m_dwPriority = 0x00000009;
	}

	return 0;
}

void CWindowUI::Render()
{
	CUI::Render();
}

void CWindowUI::Release()
{
	// ButtonVec
	for(size_t i = 0; i < m_ButtonVec.size(); ++i)
	{
		m_ButtonVec[i]->Destroy();
		m_ButtonVec[i] = NULL;
	}

	m_ButtonVec.clear();
}

void CWindowUI::Renew()
{
}

void CWindowUI::AddButton(CButtonUI* _pButtonUI)
{
	CUpdateCom* pUpdateCom = (CUpdateCom*)_pButtonUI->GetComponent(COM_TYPE_UPDATE);
	if(pUpdateCom != NULL)
		pUpdateCom->m_dwPriority = 0xFFFFFFF6;

	CRenderCom* pRenderCom = (CRenderCom*)_pButtonUI->GetComponent(COM_TYPE_RENDER);
	if(pRenderCom != NULL)
		pRenderCom->m_dwPriority = 0x00000009;

	m_ButtonVec.push_back(_pButtonUI);
}