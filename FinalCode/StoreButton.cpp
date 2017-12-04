#include "StdAfx.h"
#include "StoreButton.h"

CStoreButton::CStoreButton(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, TCHAR* _tszBackTexKey, TCHAR* _tszOverTexKey, TCHAR* _tszDownTexKey)
: CButtonUI(_tszObjKey, _eObjType, _tszBackTexKey, _tszOverTexKey, _tszDownTexKey, NULL)
{
}

CStoreButton::~CStoreButton()
{
	Release();
}

void CStoreButton::Initialize()
{
	CButtonUI::Initialize();
}

int CStoreButton::Update()
{
	DWORD dwPreState = m_dwState;

	CButtonUI::Update();

	if(dwPreState & UI_L_DOWN)
	{
		m_dwState = dwPreState;
		CUpdateCom* pUpdateCom = (CUpdateCom*)m_pComponent[COM_TYPE_UPDATE];
		if(pUpdateCom != NULL)
			pUpdateCom->m_dwPriority = 0xFFFFFFF6;

		CRenderCom* pRenderCom = (CRenderCom*)m_pComponent[COM_TYPE_RENDER];
		if(pRenderCom != NULL)
			pRenderCom->m_dwPriority = 0x00000009;
	}
	else
	{
		CUpdateCom* pUpdateCom = (CUpdateCom*)m_pComponent[COM_TYPE_UPDATE];
		if(pUpdateCom != NULL)
			pUpdateCom->m_dwPriority = 0xFFFFFFF4;

		CRenderCom* pRenderCom = (CRenderCom*)m_pComponent[COM_TYPE_RENDER];
		if(pRenderCom != NULL)
			pRenderCom->m_dwPriority = 0x0000000B;
	}

	return 0;
}

void CStoreButton::Render()
{
	CButtonUI::Render();
}

void CStoreButton::Release()
{
}