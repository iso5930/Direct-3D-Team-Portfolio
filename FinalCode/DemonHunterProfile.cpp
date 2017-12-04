#include "StdAfx.h"
#include "DemonHunterProfile.h"

CDemonHunterProfile::CDemonHunterProfile(TCHAR* _tszObjKey, OBJ_TYPE _eObjType)
: CProfileUI(_tszObjKey, _eObjType, _T("Profile_DemonHunter"))
{
}

CDemonHunterProfile::~CDemonHunterProfile(void)
{
	Release();
}

void CDemonHunterProfile::Initialize()
{
	CProfileUI::Initialize();
}

int CDemonHunterProfile::Update()
{
	CProfileUI::Update();

	return 0;
}

void CDemonHunterProfile::Render()
{
	CProfileUI::Render();
}

void CDemonHunterProfile::Release()
{
}