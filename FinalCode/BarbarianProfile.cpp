#include "StdAfx.h"
#include "BarbarianProfile.h"

CBarbarianProfile::CBarbarianProfile(TCHAR* _tszObjKey, OBJ_TYPE _eObjType)
: CProfileUI(_tszObjKey, _eObjType, _T("Profile_Barbarian"))
{
}

CBarbarianProfile::~CBarbarianProfile(void)
{
	Release();
}

void CBarbarianProfile::Initialize()
{
	CProfileUI::Initialize();
}

int CBarbarianProfile::Update()
{
	CProfileUI::Update();

	return 0;
}

void CBarbarianProfile::Render()
{
	CProfileUI::Render();
}

void CBarbarianProfile::Release()
{
}