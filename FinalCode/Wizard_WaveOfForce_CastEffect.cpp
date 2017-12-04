#include "StdAfx.h"
#include "Wizard_WaveOfForce_CastEffect.h"

CWizard_WaveOfForce_CastEffect::CWizard_WaveOfForce_CastEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{

}

CWizard_WaveOfForce_CastEffect::~CWizard_WaveOfForce_CastEffect(void)
{
	Release();
}

void CWizard_WaveOfForce_CastEffect::Initialize()
{
	CEffect::Initialize();
}

int CWizard_WaveOfForce_CastEffect::Update()
{
	CEffect::Update();

	return 0;
}

void CWizard_WaveOfForce_CastEffect::Render()
{
	CEffect::Render();
}

void CWizard_WaveOfForce_CastEffect::Release()
{

}
