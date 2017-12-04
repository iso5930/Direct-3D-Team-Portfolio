#include "StdAfx.h"
#include "WitchDoctorProfile.h"

CWitchDoctorProfile::CWitchDoctorProfile(TCHAR* _tszObjKey, OBJ_TYPE _eObjType)
: CProfileUI(_tszObjKey, _eObjType, _T("Profile_WitchDoctor"))
{
}

CWitchDoctorProfile::~CWitchDoctorProfile(void)
{
	Release();
}

void CWitchDoctorProfile::Initialize()
{
	CProfileUI::Initialize();
}

int CWitchDoctorProfile::Update()
{
	CProfileUI::Update();

	return 0;
}

void CWitchDoctorProfile::Render()
{
	CProfileUI::Render();
}

void CWitchDoctorProfile::Release()
{
}