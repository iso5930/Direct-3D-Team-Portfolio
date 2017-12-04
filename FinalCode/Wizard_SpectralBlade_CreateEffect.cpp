#include "StdAfx.h"
#include "Wizard_SpectralBlade_CreateEffect.h"

CWizard_SpectralBlade_CreateEffect::CWizard_SpectralBlade_CreateEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	m_fTime = 0.f;
	m_fAccTime = 0.f;

	// CollisionCom
	CCollisionCom* pCollisionCom = new CCollisionCom(COLL_TYPE_PLAYER_EFFECT, new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100.0f), new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100.0f));
	AddComponent(pCollisionCom);

	m_iMaxCnt = 9999;

	// Coef
	m_fCoef = 1.68f;
}

CWizard_SpectralBlade_CreateEffect::~CWizard_SpectralBlade_CreateEffect(void)
{
	Release();
}

void CWizard_SpectralBlade_CreateEffect::Initialize()
{
	CEffect::Initialize();
}

int CWizard_SpectralBlade_CreateEffect::Update()
{
	CEffect::Update();

	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();
	m_fAccTime += CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fTime >= 0.03f)
	{
		m_fTime = 0.f;

		float fAngle = D3DXToRadian(float(rand() % 360));

		float fX = float(rand() % 100) - 50.f;
		float fY = float(rand() % 100) - 50.f;

		D3DXVECTOR3 vPos = m_pTransformCom->m_vPos + D3DXVECTOR3(fX, 3.f, fY);

		CWizard_SpectralBlade_TrailEffect* pBladeEffect = new CWizard_SpectralBlade_TrailEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
		m_pLayer->AddObject(pBladeEffect, LAYER_TYPE_EFFECT);

		CTransformCom* pTransformCom = (CTransformCom*)pBladeEffect->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = vPos;
		pTransformCom->m_vAngle.y = fAngle;
		pBladeEffect->Initialize();
	}

	if(m_fAccTime >= 0.3f)
	{
		Destroy();
	}

	return 0;
}

void CWizard_SpectralBlade_CreateEffect::Render()
{
	CEffect::Render();
}

void CWizard_SpectralBlade_CreateEffect::Release()
{

}