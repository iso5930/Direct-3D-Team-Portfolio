#include "StdAfx.h"
#include "Monk_CripplingWave_RefractionEffect.h"

CMonk_CripplingWave_RefractionEffect::CMonk_CripplingWave_RefractionEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner)
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
	CCollisionCom* pCollisionCom = new CCollisionCom(COLL_TYPE_PLAYER_EFFECT, new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 110.f), new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 110.f));
	AddComponent(pCollisionCom);

	m_iMaxCnt = 100;

	m_fTime = 0.f;

	// Coef
	m_fCoef = 1.55f;
}

CMonk_CripplingWave_RefractionEffect::~CMonk_CripplingWave_RefractionEffect(void)
{
	Release();
}

void CMonk_CripplingWave_RefractionEffect::Initialize()
{
	CEffect::Initialize();

	m_pTransformCom->m_vSize = D3DXVECTOR3(0.5f, 0.5f, 0.5f);

	m_fAlpha = 0.9f;
}

int CMonk_CripplingWave_RefractionEffect::Update()
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

void CMonk_CripplingWave_RefractionEffect::Render()
{
	CEffect::Render();
}

void CMonk_CripplingWave_RefractionEffect::Release()
{

}
