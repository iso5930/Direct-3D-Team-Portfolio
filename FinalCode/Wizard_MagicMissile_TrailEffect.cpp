#include "StdAfx.h"
#include "Wizard_MagicMissile_TrailEffect.h"

CWizard_MagicMissile_TrailEffect::CWizard_MagicMissile_TrailEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, D3DXMATRIX* _pMatrix)
: CTrailEffect_2(_tszObjKey, _eObjType, 30, _pMatrix, &D3DXVECTOR3(0.f, 0.f, 30.f), &D3DXVECTOR3(0.f, 0.f, -30.f), 0.01f, _T("Effect_MagicMissile_Trail"))
{
	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_EFFECT);
	pRenderCom->m_dwPass = 2;
	AddComponent(pRenderCom);
}

CWizard_MagicMissile_TrailEffect::~CWizard_MagicMissile_TrailEffect(void)
{
	Release();
}

void CWizard_MagicMissile_TrailEffect::Initialize()
{
	CTrailEffect_2::Initialize();
}

int CWizard_MagicMissile_TrailEffect::Update()
{
	CTrailEffect_2::Update();

	return 0;
}

void CWizard_MagicMissile_TrailEffect::Render()
{
	CTrailEffect_2::Render();
}

void CWizard_MagicMissile_TrailEffect::Release()
{

}