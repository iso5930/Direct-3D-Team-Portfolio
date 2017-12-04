#include "StdAfx.h"
#include "Monk_DashingStrike_DummyEffect.h"

CMonk_DashingStrike_DummyEffect::CMonk_DashingStrike_DummyEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	m_fTime = 0.f;
	m_fAccTime = 0.f;

	// CollisionCom
	CCollisionCom* pCollisionCom = new CCollisionCom(COLL_TYPE_PLAYER_EFFECT, new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 70.f), new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 70.f));
	AddComponent(pCollisionCom);

	m_iMaxCnt = 100;

	// Coef
	m_fCoef = 3.7f;
}

CMonk_DashingStrike_DummyEffect::~CMonk_DashingStrike_DummyEffect(void)
{
	Release();
}

void CMonk_DashingStrike_DummyEffect::Initialize()
{
	CEffect::Initialize();
}

int CMonk_DashingStrike_DummyEffect::Update()
{
	CEffect::Update();

	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();
	m_fAccTime += CTimeMgr::GetInstance()->GetDeltaTime();

	m_pTransformCom->m_mWorld = ((CTransformCom*)m_pOwner->GetComponent(COM_TYPE_TRANSFORM))->m_mWorld;

	if(m_fTime >= 0.01f)
	{
		m_fTime = 0.f;

		CMonk_DashingStrike_AfterImageEffect* pAfterImage = new CMonk_DashingStrike_AfterImageEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
		m_pLayer->AddObject(pAfterImage, LAYER_TYPE_EFFECT);

		CTransformCom* pTransformCom = (CTransformCom*)pAfterImage->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = ((CTransformCom*)m_pOwner->GetComponent(COM_TYPE_TRANSFORM))->m_vPos;
		pTransformCom->m_vAngle = ((CTransformCom*)m_pOwner->GetComponent(COM_TYPE_TRANSFORM))->m_vAngle;
		pAfterImage->Initialize();
	}

	if(m_fAccTime >= 0.45f)
		Destroy();

	return 0;
}

void CMonk_DashingStrike_DummyEffect::Render()
{
	CEffect::Render();
}

void CMonk_DashingStrike_DummyEffect::Release()
{

}
