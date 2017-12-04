#include "StdAfx.h"
#include "Monk_Serenity_DummyEffect.h"

CMonk_Serenity_DummyEffect::CMonk_Serenity_DummyEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	m_fTime = 0.f;
}

CMonk_Serenity_DummyEffect::~CMonk_Serenity_DummyEffect(void)
{
	Release();
}

void CMonk_Serenity_DummyEffect::Initialize()
{
	CEffect::Initialize();
}

int CMonk_Serenity_DummyEffect::Update()
{
	CEffect::Update();

	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fTime >= 0.2f)
	{
		Destroy();

		CMonk_Serenity_DecalEffect* pDecalEffect = new CMonk_Serenity_DecalEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
		m_pOwner->GetLayer()->AddObject(pDecalEffect, LAYER_TYPE_EFFECT);

		CTransformCom* pTransformCom = (CTransformCom*)pDecalEffect->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = m_pTransformCom->m_vPos;
		pDecalEffect->Initialize();

		CMonk_Serenity_BlastWaveEffect* pWaveEffect = new CMonk_Serenity_BlastWaveEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
		m_pOwner->GetLayer()->AddObject(pWaveEffect, LAYER_TYPE_EFFECT);

		pTransformCom = (CTransformCom*)pWaveEffect->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = m_pTransformCom->m_vPos + D3DXVECTOR3(0.f, 70.f, 0.f);
		pWaveEffect->Initialize();
	}

	return 0;
}

void CMonk_Serenity_DummyEffect::Render()
{
	CEffect::Render();
}

void CMonk_Serenity_DummyEffect::Release()
{

}
