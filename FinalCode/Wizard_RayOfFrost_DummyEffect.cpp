#include "StdAfx.h"
#include "Wizard_RayOfFrost_DummyEffect.h"

CWizard_RayOfFrost_DummyEffect::CWizard_RayOfFrost_DummyEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	// CollisionCom
	m_pCollisionCom = new CCollisionCom(COLL_TYPE_PLAYER_EFFECT, new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f), new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f));
	AddComponent(m_pCollisionCom);

	m_iMaxCnt = 9999999;
	m_fTime = 0.f;

	// Coef
	m_fCoef = 2.15f;
}

CWizard_RayOfFrost_DummyEffect::~CWizard_RayOfFrost_DummyEffect(void)
{
	Release();
}

void CWizard_RayOfFrost_DummyEffect::Initialize()
{
	CEffect::Initialize();
}

int CWizard_RayOfFrost_DummyEffect::Update()
{
	CEffect::Update();

	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fTime >= 0.5f)
	{
		m_fTime = 0.f;
		m_pCollisionCom->m_pCheckSphere->ExceptVec.clear();
	}

	return 0;
}

void CWizard_RayOfFrost_DummyEffect::Render()
{
	CEffect::Render();
}

void CWizard_RayOfFrost_DummyEffect::Release()
{

}
