#include "Stdafx.h"
#include "RenderCom.h"

CRenderCom::CRenderCom(RENDER_TYPE _eRenderType)
{
	// ComType
	m_eComType = COM_TYPE_RENDER;

	// RenderType
	m_eRenderType = _eRenderType;

	// Priority
	m_dwPriority = 0x0000000F;

	// Pass
	m_dwPass = 0;

	// Color
	m_vColor = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);

	// RimColor
	m_vRimColor = D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f);
}

CRenderCom::~CRenderCom()
{
	Release();
}

void CRenderCom::Initialize()
{
}

int CRenderCom::Update()
{
	/*
	if(CInputMgr::GetInstance()->MouseDown(DIM_LBUTTON))
		++m_dwPriority;
		*/

	CRenderMgr::GetInstance()->AddObject(m_eRenderType, m_pOwner);

	return 0;
}

void CRenderCom::Render()
{
}

void CRenderCom::Release()
{
	CRenderMgr::GetInstance()->RemoveObject(m_eRenderType, m_pOwner);
}