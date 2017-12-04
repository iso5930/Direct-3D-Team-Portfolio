#include "StdAfx.h"
#include "MonkMaleBadge.h"

CMonkMaleBadge::CMonkMaleBadge(TCHAR* _tszObjKey, OBJ_TYPE _eObjType)
: CBadgeUI(_tszObjKey, _eObjType, _T("Badge_MonkMale"))
{
}

CMonkMaleBadge::~CMonkMaleBadge()
{
	Release();
}

void CMonkMaleBadge::Initialize()
{
	CBadgeUI::Initialize();
}

int CMonkMaleBadge::Update()
{
	CBadgeUI::Update();

	return 0;
}

void CMonkMaleBadge::Render()
{
	CBadgeUI::Render();
}

void CMonkMaleBadge::Release()
{
}