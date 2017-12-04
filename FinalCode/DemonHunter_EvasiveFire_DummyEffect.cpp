#include "StdAfx.h"
#include "DemonHunter_EvasiveFire_DummyEffect.h"

CDemonHunter_EvasiveFire_DummyEffect::CDemonHunter_EvasiveFire_DummyEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	// CollisionCom
	CCollisionCom* pCollisionCom = new CCollisionCom(COLL_TYPE_PLAYER_EFFECT, new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 200.f), new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 200.f));
	AddComponent(pCollisionCom);

	m_iMaxCnt = 3;

	m_fTime = 0.f;

	// Coef
	m_fCoef = 2.0f;
}

CDemonHunter_EvasiveFire_DummyEffect::~CDemonHunter_EvasiveFire_DummyEffect(void)
{
	Release();
}

void CDemonHunter_EvasiveFire_DummyEffect::Initialize()
{
	CEffect::Initialize();
}

int CDemonHunter_EvasiveFire_DummyEffect::Update()
{
	CEffect::Update();

	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fTime >= 0.2f)
	{
		Destroy();
	}

	return 0;
}

void CDemonHunter_EvasiveFire_DummyEffect::Render()
{
	CEffect::Render();
}

void CDemonHunter_EvasiveFire_DummyEffect::Release()
{

}
