#include "StdAfx.h"
#include "BarbarianMaleBadge.h"

CBarbarianMaleBadge::CBarbarianMaleBadge(TCHAR* _tszObjKey, OBJ_TYPE _eObjType)
: CBadgeUI(_tszObjKey, _eObjType, _T("Badge_BarbarianMale"))
{
}

CBarbarianMaleBadge::~CBarbarianMaleBadge()
{
	Release();
}

void CBarbarianMaleBadge::Initialize()
{
	CBadgeUI::Initialize();
}

int CBarbarianMaleBadge::Update()
{
	CBadgeUI::Update();

	return 0;
}

void CBarbarianMaleBadge::Render()
{
	CBadgeUI::Render();
}

void CBarbarianMaleBadge::Release()
{
}