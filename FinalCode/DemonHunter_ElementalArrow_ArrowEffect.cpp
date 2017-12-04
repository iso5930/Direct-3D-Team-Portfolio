#include "StdAfx.h"
#include "DemonHunter_ElementalArrow_ArrowEffect.h"

CDemonHunter_ElementalArrow_ArrowEffect::CDemonHunter_ElementalArrow_ArrowEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXVECTOR3* _pDir)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{	
	m_vDir = (*_pDir);

	// BufferCom
	CBufferCom* pBufferCom = new CBufferCom;
	pBufferCom->AddBuffer(_T("Effect_Arrow0"));
	AddComponent(pBufferCom);

	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_EFFECT);
	pRenderCom->m_dwPass = 0;
	AddComponent(pRenderCom);

	// CollisionCom
	CCollisionCom* pCollisionCom = new CCollisionCom(COLL_TYPE_PLAYER_EFFECT, new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f), new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f));
	AddComponent(pCollisionCom);

	m_pFlashEffect = NULL;
	m_pFireEffect = NULL;

	m_fTime = 0.f;

	// Coef
	m_fCoef = 3.0f;
}

CDemonHunter_ElementalArrow_ArrowEffect::~CDemonHunter_ElementalArrow_ArrowEffect(void)
{
	Release();
}

void CDemonHunter_ElementalArrow_ArrowEffect::Initialize()
{
	CEffect::Initialize();

	m_pFlashEffect = new CDemonHunter_ElementalArrow_FlashEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner, &m_pTransformCom->m_mWorld);
	m_pLayer->AddObject(m_pFlashEffect, LAYER_TYPE_EFFECT);
	m_pFlashEffect->Initialize();

	m_pFireEffect = new CDemonHunter_ElementalArrow_FireEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner, &m_pTransformCom->m_mWorld);
	m_pLayer->AddObject(m_pFireEffect, LAYER_TYPE_EFFECT);
	m_pFireEffect->Initialize();
}

int CDemonHunter_ElementalArrow_ArrowEffect::Update()
{
	CEffect::Update();

	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fTime >= 1.f)
	{
		Destroy();
	}

	if(CCameraMgr::GetInstance()->IsIn(&m_pTransformCom->m_vPos, 500.0f) == false)
		Destroy();

	m_pTransformCom->m_vPos += m_vDir * CTimeMgr::GetInstance()->GetDeltaTime();

	return 0;
}

void CDemonHunter_ElementalArrow_ArrowEffect::Render()
{
	CEffect::Render();
}

void CDemonHunter_ElementalArrow_ArrowEffect::Release()
{
	if(m_pFlashEffect != NULL)
	{
		m_pFlashEffect->Destroy();
		m_pFlashEffect = NULL;
	}

	if(m_pFireEffect != NULL)
	{
		m_pFireEffect->Destroy();
		m_pFireEffect = NULL;
	}
}		