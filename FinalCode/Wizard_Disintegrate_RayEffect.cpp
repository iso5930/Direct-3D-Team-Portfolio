#include "StdAfx.h"
#include "Wizard_Disintegrate_RayEffect.h"

CWizard_Disintegrate_RayEffect::CWizard_Disintegrate_RayEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	//BufferCom
	CBufferCom* pBufferCom = new CBufferCom;
	pBufferCom->AddBuffer(_T("Rect"));
	AddComponent(pBufferCom);

	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_EFFECT);
	pRenderCom->m_dwPass = 15;
	AddComponent(pRenderCom);

	// MaterialCom
	CMaterialCom* pMaterialCom = new CMaterialCom(NULL, _T("Effect_Disintegrate_Ray"));
	AddComponent(pMaterialCom);
}

CWizard_Disintegrate_RayEffect::~CWizard_Disintegrate_RayEffect(void)
{
	Release();
}

void CWizard_Disintegrate_RayEffect::Initialize()
{
	CEffect::Initialize();

	m_pTransformCom->m_vSize.x = 70.f;
}

int CWizard_Disintegrate_RayEffect::Update()
{
	CEffect::Update();

	return 0;
}

void CWizard_Disintegrate_RayEffect::Render()
{
	CEffect::Render();
}

void CWizard_Disintegrate_RayEffect::Release()
{

}
