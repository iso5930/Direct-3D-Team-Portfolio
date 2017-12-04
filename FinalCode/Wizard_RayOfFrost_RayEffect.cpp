#include "StdAfx.h"
#include "Wizard_RayOfFrost_RayEffect.h"

CWizard_RayOfFrost_RayEffect::CWizard_RayOfFrost_RayEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner)
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
	CMaterialCom* pMaterialCom = new CMaterialCom(NULL, _T("Effect_RayOfFrost_Ray"));
	AddComponent(pMaterialCom);
}

CWizard_RayOfFrost_RayEffect::~CWizard_RayOfFrost_RayEffect(void)
{
	Release();
}

void CWizard_RayOfFrost_RayEffect::Initialize()
{
	CEffect::Initialize();

	m_pTransformCom->m_vSize.x = 50.f;
}

int CWizard_RayOfFrost_RayEffect::Update()
{
	CEffect::Update();
	
	return 0;
}

void CWizard_RayOfFrost_RayEffect::Render()
{
	CEffect::Render();
}

void CWizard_RayOfFrost_RayEffect::Release()
{

}
