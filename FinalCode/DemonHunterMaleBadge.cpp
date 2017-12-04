#include "StdAfx.h"
#include "DemonHunterMaleBadge.h"

CDemonHunterMaleBadge::CDemonHunterMaleBadge(TCHAR* _tszObjKey, OBJ_TYPE _eObjType)
: CBadgeUI(_tszObjKey, _eObjType, _T("Badge_DemonHunterMale"))
{
}

CDemonHunterMaleBadge::~CDemonHunterMaleBadge()
{
	Release();
}

void CDemonHunterMaleBadge::Initialize()
{
	CBadgeUI::Initialize();
}

int CDemonHunterMaleBadge::Update()
{
	CBadgeUI::Update();

	return 0;
}

void CDemonHunterMaleBadge::Render()
{
	CBadgeUI::Render();
}

void CDemonHunterMaleBadge::Release()
{
}