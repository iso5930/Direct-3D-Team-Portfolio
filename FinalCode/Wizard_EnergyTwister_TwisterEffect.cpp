#include "StdAfx.h"
#include "Wizard_EnergyTwister_TwisterEffect.h"

CWizard_EnergyTwister_TwisterEffect::CWizard_EnergyTwister_TwisterEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXMATRIX* _pWorld)
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
	CMaterialCom* pMaterialCom = new CMaterialCom(NULL, _T("Effect_EnergyTwister_TwisterEffect"));
	AddComponent(pMaterialCom);

	m_pWorld = _pWorld;
}

CWizard_EnergyTwister_TwisterEffect::~CWizard_EnergyTwister_TwisterEffect(void)
{
	Release();
}

void CWizard_EnergyTwister_TwisterEffect::Initialize()
{	
	CEffect::Initialize();

	m_pTransformCom->m_vSize = D3DXVECTOR3(200.f, 10.f, 200.f);
}

int CWizard_EnergyTwister_TwisterEffect::Update()
{
	CEffect::Update();

	m_pTransformCom->m_mWorld *= *m_pWorld;

	return 0;
}

void CWizard_EnergyTwister_TwisterEffect::Render()
{
	CEffect::Render();
}

void CWizard_EnergyTwister_TwisterEffect::Release()
{

}
