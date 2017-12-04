#include "StdAfx.h"
#include "MonkFemaleBadge.h"

CMonkFemaleBadge::CMonkFemaleBadge(TCHAR* _tszObjKey, OBJ_TYPE _eObjType)
: CBadgeUI(_tszObjKey, _eObjType, _T("Badge_MonkFemale"))
{
}

CMonkFemaleBadge::~CMonkFemaleBadge()
{
	Release();
}

void CMonkFemaleBadge::Initialize()
{
	CBadgeUI::Initialize();
}

int CMonkFemaleBadge::Update()
{
	CBadgeUI::Update();

	return 0;
}

void CMonkFemaleBadge::Render()
{
	CBadgeUI::Render();
}

void CMonkFemaleBadge::Release()
{
}