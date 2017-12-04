#include "StdAfx.h"
#include "BarbarianFemaleBadge.h"

CBarbarianFemaleBadge::CBarbarianFemaleBadge(TCHAR* _tszObjKey, OBJ_TYPE _eObjType)
: CBadgeUI(_tszObjKey, _eObjType, _T("Badge_BarbarianFemale"))
{
}

CBarbarianFemaleBadge::~CBarbarianFemaleBadge()
{
	Release();
}

void CBarbarianFemaleBadge::Initialize()
{
	CBadgeUI::Initialize();
}

int CBarbarianFemaleBadge::Update()
{
	CBadgeUI::Update();

	return 0;
}

void CBarbarianFemaleBadge::Render()
{
	CBadgeUI::Render();
}

void CBarbarianFemaleBadge::Release()
{
}