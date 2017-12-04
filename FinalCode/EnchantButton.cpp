#include "StdAfx.h"
#include "EnchantButton.h"

CEnchantButton::CEnchantButton(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, TCHAR* _tszBackTexKey, TCHAR* _tszOverTexKey, TCHAR* _tszDownTexKey)
: CButtonUI(_tszObjKey, _eObjType, _tszBackTexKey, _tszOverTexKey, _tszDownTexKey, NULL)
{
}

CEnchantButton::~CEnchantButton()
{
	Release();
}

void CEnchantButton::Initialize()
{
	CButtonUI::Initialize();
}

int CEnchantButton::Update()
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

void CEnchantButton::Render()
{
	CButtonUI::Render();
}

void CEnchantButton::Release()
{
}