#include "StdAfx.h"
#include "WitchDoctorFemaleBadge.h"

CWitchDoctorFemaleBadge::CWitchDoctorFemaleBadge(TCHAR* _tszObjKey, OBJ_TYPE _eObjType)
: CBadgeUI(_tszObjKey, _eObjType, _T("Badge_WitchDoctorFemale"))
{
}

CWitchDoctorFemaleBadge::~CWitchDoctorFemaleBadge()
{
	Release();
}

void CWitchDoctorFemaleBadge::Initialize()
{
	CBadgeUI::Initialize();
}

int CWitchDoctorFemaleBadge::Update()
{
	CBadgeUI::Update();

	return 0;
}

void CWitchDoctorFemaleBadge::Render()
{
	CBadgeUI::Render();
}

void CWitchDoctorFemaleBadge::Release()
{
}