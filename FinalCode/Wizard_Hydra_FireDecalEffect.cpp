#include "StdAfx.h"
#include "Wizard_Hydra_FireDecalEffect.h"

CWizard_Hydra_FireDecalEffect::CWizard_Hydra_FireDecalEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	//BufferCom
	CBufferCom* pBufferCom = new CBufferCom;
	pBufferCom->AddBuffer(_T("Cube"));
	AddComponent(pBufferCom);

	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_EFFECT);
	pRenderCom->m_dwPass = 4;
	AddComponent(pRenderCom);

	// MaterialCom
	CMaterialCom* pMaterialCom = new CMaterialCom(NULL, _T("Effect_Meteor_Decal")); //¹Ù²Ù°í
	AddComponent(pMaterialCom);

	m_fTime = 0.f;
}

CWizard_Hydra_FireDecalEffect::~CWizard_Hydra_FireDecalEffect(void)
{
	Release();
}

void CWizard_Hydra_FireDecalEffect::Initialize()
{
	CEffect::Initialize();

	m_pTransformCom->m_vSize = D3DXVECTOR3(150.f, 10.f, 150.f);
}	

int CWizard_Hydra_FireDecalEffect::Update()
{
	CEffect::Update();

	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fTime >= 15.5f)
	{
		Destroy();
	}

	return 0;
}

void CWizard_Hydra_FireDecalEffect::Render()
{	
	CEffect::Render();
}

void CWizard_Hydra_FireDecalEffect::Release()
{

}
