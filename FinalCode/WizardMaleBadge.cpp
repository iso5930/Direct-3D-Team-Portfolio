#include "StdAfx.h"
#include "WizardMaleBadge.h"

CWizardMaleBadge::CWizardMaleBadge(TCHAR* _tszObjKey, OBJ_TYPE _eObjType)
: CBadgeUI(_tszObjKey, _eObjType, _T("Badge_WizardMale"))
{
}

CWizardMaleBadge::~CWizardMaleBadge()
{
	Release();
}

void CWizardMaleBadge::Initialize()
{
	CBadgeUI::Initialize();
}

int CWizardMaleBadge::Update()
{
	CBadgeUI::Update();

	return 0;
}

void CWizardMaleBadge::Render()
{
	CBadgeUI::Render();
}

void CWizardMaleBadge::Release()
{
}