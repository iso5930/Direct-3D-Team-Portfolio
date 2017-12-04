#include "StdAfx.h"
#include "DemonHunter_Vault_DummyEffect.h"

CDemonHunter_Vault_DummyEffect::CDemonHunter_Vault_DummyEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	m_fTime = 0.f;
	m_fAccTime = 0.f;
}

CDemonHunter_Vault_DummyEffect::~CDemonHunter_Vault_DummyEffect(void)
{
	Release();
}

void CDemonHunter_Vault_DummyEffect::Initialize()
{
	CEffect::Initialize();
}

int CDemonHunter_Vault_DummyEffect::Update()
{
	CEffect::Update();

	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();
	m_fAccTime += CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fTime >= 0.07f)
	{
		m_fTime = 0.f;

		CDemonHunter_Vault_AfterImageEffect* pAfterImageEffect = new CDemonHunter_Vault_AfterImageEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
		m_pLayer->AddObject(pAfterImageEffect, LAYER_TYPE_EFFECT);

		CTransformCom* pTransformCom = (CTransformCom*)pAfterImageEffect->GetComponent(COM_TYPE_TRANSFORM);
		CTransformCom* pOwnerTransformCom = (CTransformCom*)m_pOwner->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = pOwnerTransformCom->m_vPos;
		pTransformCom->m_vAngle = pOwnerTransformCom->m_vAngle;
		pAfterImageEffect->Initialize();
	}

	if(m_fAccTime >= 0.2f)
	{
		Destroy();
	}

	return 0;
}

void CDemonHunter_Vault_DummyEffect::Render()
{
	CEffect::Render();
}

void CDemonHunter_Vault_DummyEffect::Release()
{

}
