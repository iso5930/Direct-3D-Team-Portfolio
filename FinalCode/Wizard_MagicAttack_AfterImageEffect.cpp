#include "StdAfx.h"
#include "Wizard_MagicAttack_AfterImageEffect.h"

CWizard_MagicAttack_AfterImageEffect::CWizard_MagicAttack_AfterImageEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	
}

CWizard_MagicAttack_AfterImageEffect::~CWizard_MagicAttack_AfterImageEffect(void)
{
	Release();
}

void CWizard_MagicAttack_AfterImageEffect::Initialize()
{
	CEffect::Initialize();
}	

int CWizard_MagicAttack_AfterImageEffect::Update()
{
	CEffect::Update();

	return 0;
}

void CWizard_MagicAttack_AfterImageEffect::Render()
{
	CEffect::Render();
}

void CWizard_MagicAttack_AfterImageEffect::Release()
{

}
