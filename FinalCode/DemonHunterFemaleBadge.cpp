#include "StdAfx.h"
#include "DemonHunterFemaleBadge.h"

CDemonHunterFemaleBadge::CDemonHunterFemaleBadge(TCHAR* _tszObjKey, OBJ_TYPE _eObjType)
: CBadgeUI(_tszObjKey, _eObjType, _T("Badge_DemonHunterFemale"))
{
}

CDemonHunterFemaleBadge::~CDemonHunterFemaleBadge()
{
	Release();
}

void CDemonHunterFemaleBadge::Initialize()
{
	CBadgeUI::Initialize();
}

int CDemonHunterFemaleBadge::Update()
{
	CBadgeUI::Update();

	return 0;
}

void CDemonHunterFemaleBadge::Render()
{
	CBadgeUI::Render();
}

void CDemonHunterFemaleBadge::Release()
{
}