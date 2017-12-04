#include "StdAfx.h"
#include "Wizard_SpectralBlade_TrailEffect.h"

CWizard_SpectralBlade_TrailEffect::CWizard_SpectralBlade_TrailEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner)
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
	pRenderCom->m_dwPass = 3;
	AddComponent(pRenderCom);

	// MaterialCom
	CMaterialCom* pMaterialCom = new CMaterialCom(NULL, _T("Effect_SpectralBlade_Trail"));
	AddComponent(pMaterialCom);	

	m_fTime = 0.f;
	m_iMode = 0;
}

CWizard_SpectralBlade_TrailEffect::~CWizard_SpectralBlade_TrailEffect(void)
{
	Release();
}

void CWizard_SpectralBlade_TrailEffect::Initialize()
{
	CEffect::Initialize();

	m_pTransformCom->m_vSize = D3DXVECTOR3(200.f, 100.f, 1.f);
	m_pTransformCom->m_vAngle.x = D3DXToRadian(90.f);
}

int CWizard_SpectralBlade_TrailEffect::Update()
{
	CEffect::Update();

	switch(m_iMode)
	{
	case 0:
		Mode1();
		break;

	case 1:
		Mode2();
		break;
	}

	return 0;
}

void CWizard_SpectralBlade_TrailEffect::Render()
{
	CEffect::Render();
}

void CWizard_SpectralBlade_TrailEffect::Release()
{

}

void CWizard_SpectralBlade_TrailEffect::Mode1()
{
	m_pTransformCom->m_vSize -= D3DXVECTOR3(0.f, 1.f, 0.f) * 700.f * CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_pTransformCom->m_vSize.y <= 10.f)
	{
		++m_iMode;
	}
}

void CWizard_SpectralBlade_TrailEffect::Mode2()
{
	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fTime >= 0.3f)
	{
		Destroy();
	}
}