#include "StdAfx.h"
#include "Monk_WayOfTheHundredFists_AfterImageEffect.h"

CMonk_WayOfTheHundredFists_AfterImageEffect::CMonk_WayOfTheHundredFists_AfterImageEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXVECTOR3 _vDir)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	// BufferCom
	CBufferCom* pBufferCom = new CBufferCom;
	pBufferCom->AddBuffer(_T("Effect_WayOfTheHundredFists_Shadow"));
	AddComponent(pBufferCom);

	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_EFFECT);
	pRenderCom->m_dwPass = 19;
	AddComponent(pRenderCom);

	// CollisionCom
	CCollisionCom* pCollisionCom = new CCollisionCom(COLL_TYPE_PLAYER_EFFECT, new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.f), new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.f));
	AddComponent(pCollisionCom);

	m_iMaxCnt = 100;

	m_vDir = _vDir;
	m_fAlpha = 0.f;

	// Coef
	m_fCoef = 2.0f;
}

CMonk_WayOfTheHundredFists_AfterImageEffect::~CMonk_WayOfTheHundredFists_AfterImageEffect(void)
{
	Release();
}

void CMonk_WayOfTheHundredFists_AfterImageEffect::Initialize()
{
	CEffect::Initialize();

	m_pTransformCom->m_vSize = D3DXVECTOR3(2.f, 2.f, 2.f);
}

int CMonk_WayOfTheHundredFists_AfterImageEffect::Update()
{
	CEffect::Update();

	m_pTransformCom->m_vPos += m_vDir * CTimeMgr::GetInstance()->GetDeltaTime();

	m_fAlpha += 4.f * CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fAlpha >= 1.f)
		Destroy();

	return 0;
}

void CMonk_WayOfTheHundredFists_AfterImageEffect::Render()
{
	CEffect::Render();
}

void CMonk_WayOfTheHundredFists_AfterImageEffect::Release()
{

}
