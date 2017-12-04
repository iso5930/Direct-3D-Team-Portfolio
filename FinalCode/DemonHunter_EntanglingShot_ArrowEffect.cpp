#include "StdAfx.h"
#include "DemonHunter_EntanglingShot_ArrowEffect.h"

CDemonHunter_EntanglingShot_ArrowEffect::CDemonHunter_EntanglingShot_ArrowEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXVECTOR3* _pDir)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	// Dir
	m_vDir = *_pDir;

	// TrailEffect
	m_pTrailEffect = NULL;

	// BufferCom
	CBufferCom* pBufferCom = new CBufferCom;
	pBufferCom->AddBuffer(_T("Effect_Arrow1"));
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

	m_fTime = 0.f;

	// Coef
	m_fCoef = 2.0f;
}

CDemonHunter_EntanglingShot_ArrowEffect::~CDemonHunter_EntanglingShot_ArrowEffect(void)
{
	Release();
}

void CDemonHunter_EntanglingShot_ArrowEffect::Initialize()
{
	CEffect::Initialize();
	
	m_pTrailEffect = new CDemonHunter_EntanglingShot_ArrowTrailEffect(NULL, OBJ_TYPE_DYNAMIC, &m_pTransformCom->m_mWorld);
	m_pLayer->AddObject(m_pTrailEffect, LAYER_TYPE_EFFECT);
	m_pTrailEffect->Initialize();

	m_pTransformCom->m_vSize = D3DXVECTOR3(0.6f, 0.6f, 0.6f);
}

int CDemonHunter_EntanglingShot_ArrowEffect::Update()
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

void CDemonHunter_EntanglingShot_ArrowEffect::Render()
{
	CEffect::Render();
}

void CDemonHunter_EntanglingShot_ArrowEffect::Release()
{
	// TrailEffect
	if(m_pTrailEffect != NULL)
	{
		m_pTrailEffect->Destroy();
		m_pTrailEffect = NULL;
	}
}