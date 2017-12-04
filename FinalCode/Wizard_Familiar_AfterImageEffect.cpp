#include "StdAfx.h"
#include "Wizard_Familiar_AfterImageEffect.h"

CWizard_Familiar_AfterImageEffect::CWizard_Familiar_AfterImageEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	// BufferCom
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
	CMaterialCom* pMaterialCom = new CMaterialCom(NULL, _T("Effect_Familiar_AfterImage"));
	AddComponent(pMaterialCom);
}

CWizard_Familiar_AfterImageEffect::~CWizard_Familiar_AfterImageEffect(void)
{
	Release();
}

void CWizard_Familiar_AfterImageEffect::Initialize()
{
	CEffect::Initialize();

	m_pTransformCom->m_vSize = D3DXVECTOR3(20.f, 20.f, 1.f);
	m_pTransformCom->m_vAngle.y = D3DXToRadian(-45.f);
}

int CWizard_Familiar_AfterImageEffect::Update()
{
	CEffect::Update();

	m_pTransformCom->m_vSize -= D3DXVECTOR3(1.f, 1.f, 0.f) * 50.f * CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_pTransformCom->m_vSize.x <= 0.f)
	{
		Destroy();
	}

	return 0;
}

void CWizard_Familiar_AfterImageEffect::Render()
{
	CEffect::Render();
}

void CWizard_Familiar_AfterImageEffect::Release()
{

}
