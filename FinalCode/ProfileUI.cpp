#include "StdAfx.h"
#include "ProfileUI.h"

CProfileUI::CProfileUI(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, TCHAR* _tszBackTexKey)
: CUI(_tszObjKey, _eObjType, _tszBackTexKey)
{
	// Pos
	m_pTransformCom->m_vPos = D3DXVECTOR3(0.6f, 0.0f, 0.0f);

	// Size
	m_pTransformCom->m_vSize = D3DXVECTOR3(0.65f, 1.5f, 1.0f);
}

CProfileUI::~CProfileUI()
{
	Release();
}

void CProfileUI::Initialize()
{
	CUI::Initialize();
}

int CProfileUI::Update()
{
	CUI::Update();

	return 0;
}

void CProfileUI::Render()
{
	CUI::Render();
}

void CProfileUI::Release()
{
}