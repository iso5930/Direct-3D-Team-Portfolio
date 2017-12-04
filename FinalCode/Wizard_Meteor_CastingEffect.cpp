#include "StdAfx.h"
#include "Wizard_Meteor_CastingEffect.h"

CWizard_Meteor_CastingEffect::CWizard_Meteor_CastingEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	m_fRingCreateTime = 0.f;
	m_fMeteorCreateTime = 0.f;

	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);
}

CWizard_Meteor_CastingEffect::~CWizard_Meteor_CastingEffect(void)
{
	Release();
}

void CWizard_Meteor_CastingEffect::Initialize()
{
	CEffect::Initialize();

	m_PlayerInfo = *(CTransformCom*)m_pOwner->GetComponent(COM_TYPE_TRANSFORM);
}

int CWizard_Meteor_CastingEffect::Update()
{
	CEffect::Update();

	m_fMeteorCreateTime += CTimeMgr::GetInstance()->GetDeltaTime();
	m_fRingCreateTime += CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fRingCreateTime >= 0.05f)
	{
		m_fRingCreateTime = 0.f;

		CWizard_Meteor_RingEffect* pRingEffect = new CWizard_Meteor_RingEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
		m_pLayer->AddObject(pRingEffect, LAYER_TYPE_EFFECT);

		CTransformCom* pTransformCom = (CTransformCom*)pRingEffect->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = m_pTransformCom->m_vPos;
		pRingEffect->Initialize();
	}

	if(m_fMeteorCreateTime >= 0.7f)
	{
		Destroy();

		D3DXVECTOR3 vDir = m_pTransformCom->m_vPos - m_PlayerInfo.m_vPos;
		vDir.y = 0.f;
		D3DXVec3Normalize(&vDir, &vDir);
		vDir.y = -1.f;
				
		CWizard_Meteor_MeteorEffect* pMeteorEffect = new CWizard_Meteor_MeteorEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner, (vDir * 1000.f), m_pTransformCom->m_vPos);
		m_pLayer->AddObject(pMeteorEffect, LAYER_TYPE_EFFECT);
		
		CTransformCom* pTransformCom = (CTransformCom*)pMeteorEffect->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = m_pTransformCom->m_vPos + ((vDir * -1.f) * 500.f);
		pMeteorEffect->Initialize();
	}

	return 0;
}

void CWizard_Meteor_CastingEffect::Render()
{
	CEffect::Render();
}

void CWizard_Meteor_CastingEffect::Release()
{

}