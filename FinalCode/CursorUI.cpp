#include "StdAfx.h"
#include "CursorUI.h"

CCursorUI::CCursorUI(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, TCHAR* _tszBackTexKey)
: CUI(_tszObjKey, _eObjType, _tszBackTexKey)
{
	// Mode
	m_iMode = 0;

	// Time
	m_fTime = 0.0f;
}

CCursorUI::~CCursorUI()
{
	Release();
}

void CCursorUI::Initialize()
{
	CUI::Initialize();

	CUpdateCom* pUpdateCom = (CUpdateCom*)m_pComponent[COM_TYPE_UPDATE];
	if(pUpdateCom != NULL)
		pUpdateCom->m_dwPriority = 0xFFFFFFF5;

	CRenderCom* pRenderCom = (CRenderCom*)m_pComponent[COM_TYPE_RENDER];
	if(pRenderCom != NULL)
		pRenderCom->m_dwPriority = 0x0000000A;
}

int CCursorUI::Update()
{
	CUI::Update();

	switch(m_iMode)
	{
	case 0:
		Mode0();
		break;

	case 1:
		Mode1();
		break;
	}

	return 0;
}

void CCursorUI::Render()
{
	CUI::Render();
}

void CCursorUI::Release()
{
}

void CCursorUI::Visible()
{
	m_iMode = 0;
	m_fTime = 0.0f;

	CRenderCom* pRenderCom = (CRenderCom*)m_pComponent[COM_TYPE_RENDER];
	if(pRenderCom != NULL)
		pRenderCom->m_vColor.w = 1.0f;
}

void CCursorUI::Mode0()
{
	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();
	if(m_fTime > 0.5f)
	{
		CRenderCom* pRenderCom = (CRenderCom*)m_pComponent[COM_TYPE_RENDER];
		if(pRenderCom != NULL)
			pRenderCom->m_vColor.w = 0.0f;

		m_fTime = 0.0f;
		++m_iMode;
	}
}

void CCursorUI::Mode1()
{
	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();
	if(m_fTime > 0.5f)
	{
		CRenderCom* pRenderCom = (CRenderCom*)m_pComponent[COM_TYPE_RENDER];
		if(pRenderCom != NULL)
			pRenderCom->m_vColor.w = 1.0f;

		m_fTime = 0.0f;
		--m_iMode;
	}
}