#include "StdAfx.h"
#include "DemonHunter_FarAttack_ArrowEffect.h"

CDemonHunter_FarAttack_ArrowEffect::CDemonHunter_FarAttack_ArrowEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXVECTOR3* _pDir)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	// Dir
	m_vDir = *_pDir;

	// TrailEffect
	m_pTrailEffect = NULL;

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

	m_fTime = 0.f;
}

CDemonHunter_FarAttack_ArrowEffect::~CDemonHunter_FarAttack_ArrowEffect()
{
	Release();
}

void CDemonHunter_FarAttack_ArrowEffect::Initialize()
{
	CEffect::Initialize();

	m_pTrailEffect = new CDemonHunter_FarAttack_ArrowTrailEffect(NULL, OBJ_TYPE_DYNAMIC, &m_pTransformCom->m_mWorld);
	m_pLayer->AddObject(m_pTrailEffect, LAYER_TYPE_EFFECT);
	m_pTrailEffect->Initialize();
}

int CDemonHunter_FarAttack_ArrowEffect::Update()
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

void CDemonHunter_FarAttack_ArrowEffect::Render()
{
	CEffect::Render();
}

void CDemonHunter_FarAttack_ArrowEffect::Release()
{
	// TrailEffect
	if(m_pTrailEffect != NULL)
	{
		m_pTrailEffect->Destroy();
		m_pTrailEffect = NULL;
	}
}