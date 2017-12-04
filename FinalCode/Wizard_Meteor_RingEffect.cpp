#include "StdAfx.h"
#include "Wizard_Meteor_RingEffect.h"

CWizard_Meteor_RingEffect::CWizard_Meteor_RingEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner)
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
	CMaterialCom* pMaterialCom = new CMaterialCom(NULL, _T("Effect_Meteor_Ring"));
	AddComponent(pMaterialCom);

	m_fTime = 0.f;
}

CWizard_Meteor_RingEffect::~CWizard_Meteor_RingEffect(void)
{
	Release();
}

void CWizard_Meteor_RingEffect::Initialize()
{
	CEffect::Initialize();

	m_pTransformCom->m_vSize = D3DXVECTOR3(200.f, 200.f, 1.f);
	m_pTransformCom->m_vAngle.x = D3DXToRadian(90.f);
}

int CWizard_Meteor_RingEffect::Update()
{
	CEffect::Update();

	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();

	m_pTransformCom->m_vAngle.y += D3DXToRadian(45.f) * CTimeMgr::GetInstance()->GetDeltaTime();
	m_pTransformCom->m_vPos += D3DXVECTOR3(0.f, 1.f, 0.f) * 10.f * CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fTime >= 0.2f)
	{
		Destroy();
	}

	return 0;
}

void CWizard_Meteor_RingEffect::Render()
{
	CEffect::Render();
}

void CWizard_Meteor_RingEffect::Release()
{

}
