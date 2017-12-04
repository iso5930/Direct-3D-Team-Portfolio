#include "StdAfx.h"
#include "MonkProfile.h"

CMonkProfile::CMonkProfile(TCHAR* _tszObjKey, OBJ_TYPE _eObjType)
: CProfileUI(_tszObjKey, _eObjType, _T("Profile_Monk"))
{
}

CMonkProfile::~CMonkProfile(void)
{
	Release();
}

void CMonkProfile::Initialize()
{
	CProfileUI::Initialize();
}

int CMonkProfile::Update()
{
	CProfileUI::Update();

	return 0;
}

void CMonkProfile::Render()
{
	CProfileUI::Render();
}

void CMonkProfile::Release()
{
}