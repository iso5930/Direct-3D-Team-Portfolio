#include "StdAfx.h"
#include "Wizard_Meteor_DecalGlowEffect.h"

CWizard_Meteor_DecalGlowEffect::CWizard_Meteor_DecalGlowEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner)
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
	pRenderCom->m_dwPass = 7;
	AddComponent(pRenderCom);

	// MaterialCom
	CMaterialCom* pMaterialCom = new CMaterialCom(NULL, _T("Effect_Meteor_DecalGlow"));
	AddComponent(pMaterialCom);

	m_iMode = 0;
	m_fTime = 0.f;
	m_fAlpha = 0.f;
}

CWizard_Meteor_DecalGlowEffect::~CWizard_Meteor_DecalGlowEffect(void)
{
	Release();
}

void CWizard_Meteor_DecalGlowEffect::Initialize()
{
	CEffect::Initialize();

	m_pTransformCom->m_vSize = D3DXVECTOR3(300.f, 300.f, 300.f);
}

int CWizard_Meteor_DecalGlowEffect::Update()
{
	CEffect::Update();

	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fTime >= 3.0f)
	{
		Destroy(); 
	}

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

void CWizard_Meteor_DecalGlowEffect::Render()
{
	CEffect::Render();
}

void CWizard_Meteor_DecalGlowEffect::Release()
{

}

void CWizard_Meteor_DecalGlowEffect::Mode1()
{
	if(m_fAlpha <= 0.f)
	{
		++m_iMode;
	}

	m_fAlpha -= 0.5f * CTimeMgr::GetInstance()->GetDeltaTime();
}

void CWizard_Meteor_DecalGlowEffect::Mode2()
{
	if(m_fAlpha >= 0.2f)
	{
		--m_iMode;
	}

	m_fAlpha += 0.5f * CTimeMgr::GetInstance()->GetDeltaTime();
}