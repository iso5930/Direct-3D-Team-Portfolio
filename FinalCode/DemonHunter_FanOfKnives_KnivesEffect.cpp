#include "StdAfx.h"
#include "DemonHunter_FanOfKnives_KnivesEffect.h"

CDemonHunter_FanOfKnives_KnivesEffect::CDemonHunter_FanOfKnives_KnivesEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXVECTOR3* _pDir)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	m_vDir = (*_pDir);

	//BufferCom
	CBufferCom* pBufferCom = new CBufferCom;
	pBufferCom->AddBuffer(_T("Effect_Impale"));
	AddComponent(pBufferCom);

	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_EFFECT);
	pRenderCom->m_dwPass = 0;
	AddComponent(pRenderCom);

	// CollisionCom
	CCollisionCom* pCollisionCom = new CCollisionCom(COLL_TYPE_PLAYER_EFFECT, new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100.0f), new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100.0f));
	AddComponent(pCollisionCom);

	m_fTime = 0.f;

	m_pTrailEffect = NULL;

	m_iMaxCnt = 100;

	// Coef
	m_fCoef = 6.2f;
}

CDemonHunter_FanOfKnives_KnivesEffect::~CDemonHunter_FanOfKnives_KnivesEffect(void)
{
	Release();
}

void CDemonHunter_FanOfKnives_KnivesEffect::Initialize()
{
	CEffect::Initialize();

	m_pTransformCom->m_vSize = D3DXVECTOR3(2.5f, 2.5f, 2.5f);
	
	m_pTrailEffect = new CDemonHunter_FanOfKnives_TrailEffect(NULL, OBJ_TYPE_DYNAMIC, &m_pTransformCom->m_mWorld);
	m_pLayer->AddObject(m_pTrailEffect, LAYER_TYPE_EFFECT);
	m_pTrailEffect->Initialize();
}

int CDemonHunter_FanOfKnives_KnivesEffect::Update()
{
	CEffect::Update();

	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fTime >= 0.2f)
		Destroy();

	m_pTransformCom->m_vPos += m_vDir * CTimeMgr::GetInstance()->GetDeltaTime();

	return 0;
}

void CDemonHunter_FanOfKnives_KnivesEffect::Render()
{	
	CEffect::Render();
}

void CDemonHunter_FanOfKnives_KnivesEffect::Release()
{
	if(m_pTrailEffect != NULL)
	{
		m_pTrailEffect->Destroy();
		m_pTrailEffect = NULL;
	}
}