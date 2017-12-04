#include "StdAfx.h"
#include "Wizard_ArcaneOrb_DestoryEffect.h"

CWizard_ArcaneOrb_DestoryEffect::CWizard_ArcaneOrb_DestoryEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	//BufferCom
	CBufferCom* pBufferCom = new CBufferCom;
	pBufferCom->AddBuffer(_T("Effect_SlowTime"));
	AddComponent(pBufferCom);

	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_EFFECT);
	pRenderCom->m_dwPass = 13;
	AddComponent(pRenderCom);

	m_fTime = 0.0f;
}

CWizard_ArcaneOrb_DestoryEffect::~CWizard_ArcaneOrb_DestoryEffect(void)
{
	Release();
}

void CWizard_ArcaneOrb_DestoryEffect::Initialize()
{
	CEffect::Initialize();

	m_fAlpha = 0.9f;

	m_pTransformCom->m_vSize = D3DXVECTOR3(0.5f, 0.5f, 0.5f);
}

int CWizard_ArcaneOrb_DestoryEffect::Update()
{
	CEffect::Update();

	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();

	m_pTransformCom->m_vSize += D3DXVECTOR3(1.f, 1.f, 1.f) * CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fTime >= 0.3f)
		Destroy();

	return 0;
}	

void CWizard_ArcaneOrb_DestoryEffect::Render()
{
	CEffect::Render();
}

void CWizard_ArcaneOrb_DestoryEffect::Release()
{

}
