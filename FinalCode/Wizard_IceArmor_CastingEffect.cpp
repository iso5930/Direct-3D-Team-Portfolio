#include "StdAfx.h"
#include "Wizard_IceArmor_CastingEffect.h"

CWizard_IceArmor_CastingEffect::CWizard_IceArmor_CastingEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	// BufferCom
	CBufferCom* pBufferCom = new CBufferCom;
	pBufferCom->AddBuffer(_T("Effect_IceArmor"));
	AddComponent(pBufferCom);

	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_EFFECT);
	pRenderCom->m_dwPass = 9;
	AddComponent(pRenderCom);

	m_fTime = 0.f;
}

CWizard_IceArmor_CastingEffect::~CWizard_IceArmor_CastingEffect(void)
{
	Release();
}

void CWizard_IceArmor_CastingEffect::Initialize()
{
	CEffect::Initialize();

	m_pTransformCom->m_vSize = D3DXVECTOR3(2.5f, 2.5f, 2.5f);
}

int CWizard_IceArmor_CastingEffect::Update()
{
	CTransformCom* pTransformCom = (CTransformCom*)m_pOwner->GetComponent(COM_TYPE_TRANSFORM);

	m_pTransformCom->m_vPos = pTransformCom->m_vPos + D3DXVECTOR3(0.f, 70.f, 0.f);

	CEffect::Update();

	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fTime >= 1800.f)
	{
		Destroy();
	}

	m_pTransformCom->m_vAngle.y += D3DXToRadian(30.f) * 10.f * CTimeMgr::GetInstance()->GetDeltaTime();

	return 0;
}

void CWizard_IceArmor_CastingEffect::Render()
{
	CEffect::Render();
}

void CWizard_IceArmor_CastingEffect::Release()
{

}
