#include "StdAfx.h"
#include "Wizard_StormArmor_CastingEffect.h"

CWizard_StormArmor_CastingEffect::CWizard_StormArmor_CastingEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	m_fTime = 0.f;
	m_fAccTime = 0.f;
}

CWizard_StormArmor_CastingEffect::~CWizard_StormArmor_CastingEffect(void)
{
	Release();
}

void CWizard_StormArmor_CastingEffect::Initialize()
{
	CEffect::Initialize();
}	

int CWizard_StormArmor_CastingEffect::Update()
{
	CEffect::Update();
	
	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();
	m_fAccTime += CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fTime >= 0.05f)
	{
		m_fTime = 0.f;

		int iX = (rand() % 50) - 25;
		int iY = rand() % 50;
		int iZ = (rand() % 50) - 25;

		CTransformCom* pOwnerTransformCom = (CTransformCom*)m_pOwner->GetComponent(COM_TYPE_TRANSFORM);
		
		CWizard_StormArmor_LightningEffect* pLightningEffect = new CWizard_StormArmor_LightningEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
		m_pLayer->AddObject(pLightningEffect, LAYER_TYPE_EFFECT);

		CTransformCom* pTransformCom = (CTransformCom*)pLightningEffect->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = pOwnerTransformCom->m_vPos + D3DXVECTOR3(float(iX), float(iY) + 30.f, float(iZ));
		pLightningEffect->Initialize();
	}

	if(m_fAccTime >= 2.f)
	{
		Destroy();

		CWizard_StormArmor_BuffEffect* pBuffEffect = new CWizard_StormArmor_BuffEffect(_T("Armor"), OBJ_TYPE_DYNAMIC, m_pOwner);
		m_pLayer->AddObject(pBuffEffect, LAYER_TYPE_EFFECT);
		pBuffEffect->Initialize();
	}

	return 0;
}

void CWizard_StormArmor_CastingEffect::Render()
{
	CEffect::Render();
}

void CWizard_StormArmor_CastingEffect::Release()
{

}
