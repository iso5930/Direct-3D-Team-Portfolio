#include "StdAfx.h"
#include "Monk_WayOfTheHundredFists_ShockWaveRefractionEffect.h"

CMonk_WayOfTheHundredFists_ShockWaveRefractionEffect::CMonk_WayOfTheHundredFists_ShockWaveRefractionEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	// BufferCom
	CBufferCom* pBufferCom = new CBufferCom;
	pBufferCom->AddBuffer(_T("Effect_SlowTime"));
	AddComponent(pBufferCom);

	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_EFFECT);
	pRenderCom->m_dwPass = 13;
	AddComponent(pRenderCom);

	// CollisionCom
	CCollisionCom* pCollisionCom = new CCollisionCom(COLL_TYPE_PLAYER_EFFECT, new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 70.f), new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 70.f));
	AddComponent(pCollisionCom);

	m_iMaxCnt = 100;

	m_fTime = 0.f;

	// Coef
	m_fCoef = 2.0f;
}

CMonk_WayOfTheHundredFists_ShockWaveRefractionEffect::~CMonk_WayOfTheHundredFists_ShockWaveRefractionEffect(void)
{
	Release();
}

void CMonk_WayOfTheHundredFists_ShockWaveRefractionEffect::Initialize()
{
	CEffect::Initialize();

	m_pTransformCom->m_vSize = D3DXVECTOR3(0.5f, 0.5f, 0.5f);

	m_fAlpha = 0.9f;
}

int CMonk_WayOfTheHundredFists_ShockWaveRefractionEffect::Update()
{
	CEffect::Update();

	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();

	m_pTransformCom->m_vSize += D3DXVECTOR3(1.f, 1.f, 1.f) * CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fTime >= 0.3f)
	{
		Destroy();
	}

	return 0;
}

void CMonk_WayOfTheHundredFists_ShockWaveRefractionEffect::Render()
{
	CEffect::Render();
}	

void CMonk_WayOfTheHundredFists_ShockWaveRefractionEffect::Release()
{

}
