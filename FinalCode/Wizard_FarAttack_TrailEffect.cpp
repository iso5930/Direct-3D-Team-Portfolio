#include "StdAfx.h"
#include "Wizard_FarAttack_TrailEffect.h"

CWizard_FarAttack_TrailEffect::CWizard_FarAttack_TrailEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, D3DXMATRIX* _pMatrix)
: CTrailEffect(_tszObjKey, _eObjType, 50, _pMatrix, &D3DXVECTOR3(0.0f, 10.0f, 0.0f), &D3DXVECTOR3(0.0f, -10.0f, 0.0f), 0.01f, _T("Effect_ArrowTrail"))
{
	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_EFFECT);
	pRenderCom->m_dwPass = 1;
	AddComponent(pRenderCom);
}

CWizard_FarAttack_TrailEffect::~CWizard_FarAttack_TrailEffect(void)
{
	Release();
}

void CWizard_FarAttack_TrailEffect::Initialize()
{
	CTrailEffect::Initialize();
}

int CWizard_FarAttack_TrailEffect::Update()
{
	CTrailEffect::Update();

	return 0;
}	

void CWizard_FarAttack_TrailEffect::Render()
{
	CTrailEffect::Render();
}

void CWizard_FarAttack_TrailEffect::Release()
{

}

