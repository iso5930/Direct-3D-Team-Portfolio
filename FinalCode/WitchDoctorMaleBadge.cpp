#include "StdAfx.h"
#include "WitchDoctorMaleBadge.h"

CWitchDoctorMaleBadge::CWitchDoctorMaleBadge(TCHAR* _tszObjKey, OBJ_TYPE _eObjType)
: CBadgeUI(_tszObjKey, _eObjType, _T("Badge_WitchDoctorMale"))
{
}

CWitchDoctorMaleBadge::~CWitchDoctorMaleBadge()
{
	Release();
}

void CWitchDoctorMaleBadge::Initialize()
{
	CBadgeUI::Initialize();
}

int CWitchDoctorMaleBadge::Update()
{
	CBadgeUI::Update();

	return 0;
}

void CWitchDoctorMaleBadge::Render()
{
	CBadgeUI::Render();
}

void CWitchDoctorMaleBadge::Release()
{
}