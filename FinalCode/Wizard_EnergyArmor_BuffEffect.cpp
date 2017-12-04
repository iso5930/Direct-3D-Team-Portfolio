#include "StdAfx.h"
#include "Wizard_EnergyArmor_BuffEffect.h"

CWizard_EnergyArmor_BuffEffect::CWizard_EnergyArmor_BuffEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXVECTOR3* _pPos)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	// BufferCom
	CBufferCom* pBufferCom = new CBufferCom;
	pBufferCom->AddBuffer(_T("Effect_EnergyArmor"));
	AddComponent(pBufferCom);

	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_EFFECT);
	pRenderCom->m_dwPass = 13;
	AddComponent(pRenderCom);

	m_fTime = 0.f;
	m_fAlpha = 0.5f;

	m_pPos = _pPos;
}

CWizard_EnergyArmor_BuffEffect::~CWizard_EnergyArmor_BuffEffect(void)
{
	Release();
}

void CWizard_EnergyArmor_BuffEffect::Initialize()
{
	CEffect::Initialize();

	m_pTransformCom->m_vSize = D3DXVECTOR3(0.4f, 0.4f, 0.4f);
}

int CWizard_EnergyArmor_BuffEffect::Update()
{
	CEffect::Update();

	m_pTransformCom->m_vPos = *m_pPos + D3DXVECTOR3(0.f, 50.f, 0.f);

	m_pTransformCom->m_vAngle.y = D3DXToRadian(float(rand() % 360));

	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fTime >= 1800.f)
		Destroy();

	return 0;
}

void CWizard_EnergyArmor_BuffEffect::Render()
{
	CEffect::Render();
}

void CWizard_EnergyArmor_BuffEffect::Release()
{

}
