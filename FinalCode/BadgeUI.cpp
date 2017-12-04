#include "StdAfx.h"
#include "BadgeUI.h"

CBadgeUI::CBadgeUI(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, TCHAR* _tszBackTexKey)
: CUI(_tszObjKey, _eObjType, _tszBackTexKey)
{
	// Pos
	m_pTransformCom->m_vPos = D3DXVECTOR3(0.0f, -0.67f, 0.0f);

	// Size
	m_pTransformCom->m_vSize = D3DXVECTOR3(0.1f, 0.1466f, 1.0f);
}

CBadgeUI::~CBadgeUI()
{
	Release();
}

void CBadgeUI::Initialize()
{
	CUI::Initialize();
}

int CBadgeUI::Update()
{
	CUI::Update();

	return 0;
}

void CBadgeUI::Render()
{
	CUI::Render();
}

void CBadgeUI::Release()
{
}