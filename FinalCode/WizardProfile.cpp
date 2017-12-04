#include "StdAfx.h"
#include "WizardProfile.h"

CWizardProfile::CWizardProfile(TCHAR* _tszObjKey, OBJ_TYPE _eObjType)
: CProfileUI(_tszObjKey, _eObjType, _T("Profile_Wizard"))
{
}

CWizardProfile::~CWizardProfile(void)
{
	Release();
}

void CWizardProfile::Initialize()
{
	CProfileUI::Initialize();
}

int CWizardProfile::Update()
{
	CProfileUI::Update();

	return 0;
}

void CWizardProfile::Render()
{
	CProfileUI::Render();
}

void CWizardProfile::Release()
{
}