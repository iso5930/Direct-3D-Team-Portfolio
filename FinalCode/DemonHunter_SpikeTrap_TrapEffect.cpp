#include "StdAfx.h"
#include "DemonHunter_SpikeTrap_TrapEffect.h"

CDemonHunter_SpikeTrap_TrapEffect::CDemonHunter_SpikeTrap_TrapEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	m_pDecalEffect = NULL;
	m_pDecalGlowEffect = NULL;
	m_pSpikeEffect = NULL;
	m_pFireEffect = NULL;

	m_iPrevHate = 0;
}

CDemonHunter_SpikeTrap_TrapEffect::~CDemonHunter_SpikeTrap_TrapEffect(void)
{
	Release();
}

void CDemonHunter_SpikeTrap_TrapEffect::Initialize()
{
	CEffect::Initialize();

	m_pDecalEffect = new CDemonHunter_SpikeTrap_DecalEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
	m_pOwner->GetLayer()->AddObject(m_pDecalEffect, LAYER_TYPE_EFFECT);

	CTransformCom* pTransformCom = (CTransformCom*)m_pDecalEffect->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = m_pTransformCom->m_vPos;
	m_pDecalEffect->Initialize();

	m_pDecalGlowEffect = new CDemonHunter_SpikeTrap_DecalGlowEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
	m_pOwner->GetLayer()->AddObject(m_pDecalGlowEffect, LAYER_TYPE_EFFECT);

	pTransformCom = (CTransformCom*)m_pDecalGlowEffect->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = m_pTransformCom->m_vPos;
	m_pDecalGlowEffect->Initialize();

	m_pSpikeEffect = new CDemonHunter_SpikeTrap_SpikeEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
	m_pOwner->GetLayer()->AddObject(m_pSpikeEffect, LAYER_TYPE_EFFECT);

	pTransformCom = (CTransformCom*)m_pSpikeEffect->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = m_pTransformCom->m_vPos;
	m_pSpikeEffect->Initialize();

	m_pFireEffect = new CDemonHunter_SpikeTrap_FireEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
	m_pOwner->GetLayer()->AddObject(m_pFireEffect, LAYER_TYPE_EFFECT);

	pTransformCom = (CTransformCom*)m_pFireEffect->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = m_pTransformCom->m_vPos;
	m_pFireEffect->Initialize();
}

int CDemonHunter_SpikeTrap_TrapEffect::Update()
{
	CEffect::Update();

	int iHate = ((CPlayer*)m_pOwner)->GetStat()->iHate;

	if(iHate < m_iPrevHate)
	{
		Destroy();

		CDemonHunter_SpikeTrap_BombEffect* pBombEffect = new CDemonHunter_SpikeTrap_BombEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
		m_pLayer->AddObject(pBombEffect, LAYER_TYPE_EFFECT);

		CTransformCom* pTrnasformCom = (CTransformCom*)pBombEffect->GetComponent(COM_TYPE_TRANSFORM);
		pTrnasformCom->m_vPos = m_pTransformCom->m_vPos + D3DXVECTOR3(0.f, 150.f, 0.f);
		pBombEffect->Initialize();
	}
	else
		m_iPrevHate = iHate;

	return 0;
}

void CDemonHunter_SpikeTrap_TrapEffect::Render()
{
	CEffect::Render();
}

void CDemonHunter_SpikeTrap_TrapEffect::Release()
{
	m_pDecalEffect->Destroy();
	m_pDecalGlowEffect->Destroy();
	m_pFireEffect->Destroy();
	m_pSpikeEffect->Destroy();
}