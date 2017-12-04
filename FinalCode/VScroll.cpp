#include "StdAfx.h"
#include "VScroll.h"

CVScroll::CVScroll(TCHAR* _tszObjKey, OBJ_TYPE _eObjType)
: CScrollUI(_tszObjKey, _eObjType, _T("Scroll_Back_Vertical"), _T("Scroll_Over_Vertical"), _T("Scroll_Down_Vertical"))
{
}

CVScroll::~CVScroll()
{
	Release();
}

void CVScroll::Initialize()
{
	CScrollUI::Initialize();
}

int CVScroll::Update()
{
	if(m_bClicked)
	{
		D3DXVECTOR3 vMousePos;
		ScreenToProj(&vMousePos, CInputMgr::GetInstance()->GetMousePos());

		if(m_pTransformCom->m_vPos.y - m_pTransformCom->m_vSize.y > vMousePos.y)
		{
			if(++m_iScroll > m_iMaxScroll)
				m_iScroll = m_iMaxScroll;
		}
		else if(m_pTransformCom->m_vPos.y + m_pTransformCom->m_vSize.y < vMousePos.y)
		{
			if(--m_iScroll < 0)
				m_iScroll = 0;
		}
	}

	m_pTransformCom->m_vSize.y = (m_fMax - m_fMin) / (m_iMaxScroll + 1);
	m_pTransformCom->m_vPos.y = m_fMax - m_pTransformCom->m_vSize.y / 2.0f - m_pTransformCom->m_vSize.y * m_iScroll;

	CScrollUI::Update();

	return 0;
}

void CVScroll::Render()
{
	CScrollUI::Render();
}

void CVScroll::Release()
{
}