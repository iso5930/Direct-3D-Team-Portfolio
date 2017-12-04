#include "StdAfx.h"
#include "Monk_WayOfTheHundredFists_DummyEffect.h"

CMonk_WayOfTheHundredFists_DummyEffect::CMonk_WayOfTheHundredFists_DummyEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXVECTOR3 _vDir)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	m_vDir = _vDir;
	m_fTime = 0.f;

	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	m_pTrailEffect = NULL;

	// CollisionCom
	CCollisionCom* pCollisionCom = new CCollisionCom(COLL_TYPE_PLAYER_EFFECT, new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 30.f), new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 30.f));
	AddComponent(pCollisionCom);

	m_iMaxCnt = 100;

	// Coef
	m_fCoef = 2.0f;
}

CMonk_WayOfTheHundredFists_DummyEffect::~CMonk_WayOfTheHundredFists_DummyEffect(void)
{
	Release();
}

void CMonk_WayOfTheHundredFists_DummyEffect::Initialize()
{
	CEffect::Initialize();

	m_pTrailEffect = new CMonk_WayOfTheHundredFists_TrailEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner, &m_pTransformCom->m_mWorld);
	m_pLayer->AddObject(m_pTrailEffect, LAYER_TYPE_EFFECT);
	m_pTrailEffect->Initialize();
}

int CMonk_WayOfTheHundredFists_DummyEffect::Update()
{
	CEffect::Update();

	float fTime = CTimeMgr::GetInstance()->GetDeltaTime();

	m_fTime += fTime;

	m_pTransformCom->m_vPos += m_vDir * fTime;

	if(m_fTime >= 0.2f)
		Destroy();

	return 0;
}

void CMonk_WayOfTheHundredFists_DummyEffect::Render()
{
	CEffect::Render();
}

void CMonk_WayOfTheHundredFists_DummyEffect::Release()
{
	if(m_pTrailEffect != NULL)
	{
		m_pTrailEffect->Destroy();
		m_pTrailEffect = NULL;
	}
}