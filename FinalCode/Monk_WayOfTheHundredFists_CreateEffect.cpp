#include "StdAfx.h"
#include "Monk_WayOfTheHundredFists_CreateEffect.h"

CMonk_WayOfTheHundredFists_CreateEffect::CMonk_WayOfTheHundredFists_CreateEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, float _fTime, DWORD _dwNum)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	m_fTime = 0.f;
	m_fCreateTime = _fTime;
	m_dwNum = _dwNum;
	m_iMode = 0;
	m_fAccTime = 0.f;

	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);
}

CMonk_WayOfTheHundredFists_CreateEffect::~CMonk_WayOfTheHundredFists_CreateEffect(void)
{
	Release();
}

void CMonk_WayOfTheHundredFists_CreateEffect::Initialize()
{
	CEffect::Initialize();
}	

int CMonk_WayOfTheHundredFists_CreateEffect::Update()
{
	CEffect::Update();

	switch(m_iMode)
	{
	case 0:
		Mode1();
		break;

	case 1:
		Mode2();
		break;
	}

	return 0;
}

void CMonk_WayOfTheHundredFists_CreateEffect::Render()
{
	CEffect::Render();
}

void CMonk_WayOfTheHundredFists_CreateEffect::Release()
{

}

void CMonk_WayOfTheHundredFists_CreateEffect::Mode1()
{
	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fTime >= m_fCreateTime)
	{
		m_fTime = 0.f;
		++m_iMode;
	}
}

void CMonk_WayOfTheHundredFists_CreateEffect::Mode2()
{
	if(m_dwNum == 2)
	{
		Destroy();

		CTransformCom* pOwnerTransformCom = (CTransformCom*)m_pOwner->GetComponent(COM_TYPE_TRANSFORM);	

		CMonk_WayOfTheHundredFists_ShockWaveRefractionEffect* pShockEffect = new CMonk_WayOfTheHundredFists_ShockWaveRefractionEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
		m_pLayer->AddObject(pShockEffect, LAYER_TYPE_EFFECT);

		CTransformCom* pTransformCom = (CTransformCom*)pShockEffect->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = pOwnerTransformCom->m_vPos + (pOwnerTransformCom->m_vAxisZ * -1.f * 50.f) + D3DXVECTOR3(0.f, 80.f, 0.f);
		pShockEffect->Initialize();

		CMonk_WayOfTheHundredFists_ShockWaveDecalEffect* pDecalEffect = new CMonk_WayOfTheHundredFists_ShockWaveDecalEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
		m_pLayer->AddObject(pDecalEffect, LAYER_TYPE_EFFECT);

		pTransformCom = (CTransformCom*)pDecalEffect->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = pOwnerTransformCom->m_vPos + (pOwnerTransformCom->m_vAxisZ * 50.f * -1.f);
		pDecalEffect->Initialize();

		CMonk_WayOfTheHundredFists_DummyEffect* pDummyEffect = new CMonk_WayOfTheHundredFists_DummyEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner, pOwnerTransformCom->m_vAxisZ * -1.f * 1200.f);
		m_pLayer->AddObject(pDummyEffect, LAYER_TYPE_EFFECT);

		pTransformCom = (CTransformCom*)pDummyEffect->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = pOwnerTransformCom->m_vPos + D3DXVECTOR3(0.f, 60.f, 0.f);
		pDummyEffect->Initialize();
	}
	else if(m_dwNum == 1)
	{
		m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();
		m_fAccTime += CTimeMgr::GetInstance()->GetDeltaTime();

		if(m_fTime >= 0.1f)
		{
			m_fTime = 0.f;

			CTransformCom* pOwnerTransformCom = (CTransformCom*)m_pOwner->GetComponent(COM_TYPE_TRANSFORM);	

			D3DXVECTOR3 vDir = pOwnerTransformCom->m_vAxisZ * -1.f;
			
			float fAngle = D3DXToRadian(float((rand() % 45) - 22.5f));

			D3DXMATRIX matRotY;
			D3DXMatrixRotationY(&matRotY, fAngle);
			D3DXVec3TransformNormal(&vDir, &vDir, &matRotY);

			CMonk_WayOfTheHundredFists_DummyEffect* pDummyEffect = new CMonk_WayOfTheHundredFists_DummyEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner, vDir * 1000.f);
			m_pLayer->AddObject(pDummyEffect, LAYER_TYPE_EFFECT);

			CTransformCom* pTransformCom = (CTransformCom*)pDummyEffect->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vPos = pOwnerTransformCom->m_vPos + D3DXVECTOR3(0.f, 60.f, 0.f);
			pDummyEffect->Initialize();
		}

		if(m_fAccTime >= 0.7f)
		{
			Destroy();
		}
	}
	else
	{
		Destroy();

		CTransformCom* pOwnerTransformCom = (CTransformCom*)m_pOwner->GetComponent(COM_TYPE_TRANSFORM);	

		D3DXVECTOR3 vDir = pOwnerTransformCom->m_vAxisZ * -1.f * 1000.f;

		CMonk_WayOfTheHundredFists_AfterImageEffect* pAfterImage = new CMonk_WayOfTheHundredFists_AfterImageEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner, vDir);
		m_pLayer->AddObject(pAfterImage, LAYER_TYPE_EFFECT);

		CTransformCom* pTransformCom = (CTransformCom*)pAfterImage->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = pOwnerTransformCom->m_vPos + pOwnerTransformCom->m_vAxisZ * 170.f;
		pTransformCom->m_vAngle = pOwnerTransformCom->m_vAngle;
		pAfterImage->Initialize();
	}
}	