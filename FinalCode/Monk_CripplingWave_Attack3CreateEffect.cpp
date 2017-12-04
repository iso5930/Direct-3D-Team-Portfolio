#include "StdAfx.h"
#include "Monk_CripplingWave_Attack3CreateEffect.h"

CMonk_CripplingWave_Attack3CreateEffect::CMonk_CripplingWave_Attack3CreateEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	m_fTime = 0.f;
}

CMonk_CripplingWave_Attack3CreateEffect::~CMonk_CripplingWave_Attack3CreateEffect(void)
{
	Release();
}

void CMonk_CripplingWave_Attack3CreateEffect::Initialize()
{
	CEffect::Initialize();
}

int CMonk_CripplingWave_Attack3CreateEffect::Update()
{
	CEffect::Update();

	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fTime >= 0.3f)
	{
		Destroy();

		CTransformCom* pOwnerInfo = (CTransformCom*)m_pOwner->GetComponent(COM_TYPE_TRANSFORM);
		
		CMonk_CripplingWave_Attack3Effect* pAttack3 = new CMonk_CripplingWave_Attack3Effect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
		m_pOwner->GetLayer()->AddObject(pAttack3, LAYER_TYPE_EFFECT);

		CTransformCom* pTransformCom = (CTransformCom*)pAttack3->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = pOwnerInfo->m_vPos;
		pTransformCom->m_vAngle = pOwnerInfo->m_vAngle;
		pAttack3->Initialize();

		CMonk_CripplingWave_RefractionEffect* pRefraction = new CMonk_CripplingWave_RefractionEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
		m_pOwner->GetLayer()->AddObject(pRefraction, LAYER_TYPE_EFFECT);

		pTransformCom = (CTransformCom*)pRefraction->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = pOwnerInfo->m_vPos + D3DXVECTOR3(0.f, 70.f, 0.f);
		pRefraction->Initialize();

		CMonk_CripplingWave_DecalEffect* pDecalEffect = new CMonk_CripplingWave_DecalEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
		m_pOwner->GetLayer()->AddObject(pDecalEffect, LAYER_TYPE_EFFECT);

		pTransformCom = (CTransformCom*)pDecalEffect->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = pOwnerInfo->m_vPos;
		pDecalEffect->Initialize();

		CMonk_CripplingWave_DecalGlowEffect* pGlowEffect = new CMonk_CripplingWave_DecalGlowEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
		m_pOwner->GetLayer()->AddObject(pGlowEffect, LAYER_TYPE_EFFECT);

		pTransformCom = (CTransformCom*)pGlowEffect->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = pOwnerInfo->m_vPos;
		pGlowEffect->Initialize();
	}

	return 0;
}

void CMonk_CripplingWave_Attack3CreateEffect::Render()
{	
	CEffect::Render();
}

void CMonk_CripplingWave_Attack3CreateEffect::Release()
{

}
