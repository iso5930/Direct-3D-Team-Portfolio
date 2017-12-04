#include "StdAfx.h"
#include "WizardFemaleBadge.h"

CWizardFemaleBadge::CWizardFemaleBadge(TCHAR* _tszObjKey, OBJ_TYPE _eObjType)
: CBadgeUI(_tszObjKey, _eObjType, _T("Badge_WizardFemale"))
{
}

CWizardFemaleBadge::~CWizardFemaleBadge()
{
	Release();
}

void CWizardFemaleBadge::Initialize()
{
	CBadgeUI::Initialize();
}

int CWizardFemaleBadge::Update()
{
	CBadgeUI::Update();

	return 0;
}

void CWizardFemaleBadge::Render()
{
	CBadgeUI::Render();
}

void CWizardFemaleBadge::Release()
{
}