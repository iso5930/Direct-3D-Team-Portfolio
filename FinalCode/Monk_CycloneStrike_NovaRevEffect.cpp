#include "StdAfx.h"
#include "Monk_CycloneStrike_NovaRevEffect.h"

CMonk_CycloneStrike_NovaRevEffect::CMonk_CycloneStrike_NovaRevEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	// BufferCom
	CBufferCom* pBufferCom = new CBufferCom;
	pBufferCom->AddBuffer(_T("Effect_CycloneStrike_Nova"));
	AddComponent(pBufferCom);

	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_EFFECT);
	pRenderCom->m_dwPass = 17;
	AddComponent(pRenderCom);

	// MaterialCom
	CMaterialCom* pMaterialCom = new CMaterialCom(NULL, _T("Effect_BreathOfHeaven_Alpha"));
	AddComponent(pMaterialCom);

	m_fTime = 0.f;

	// CollisionCom
	CCollisionCom* pCollisionCom = new CCollisionCom(COLL_TYPE_PLAYER_EFFECT, new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100.f), new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100.f));
	AddComponent(pCollisionCom);

	m_iMaxCnt = 100;
}

CMonk_CycloneStrike_NovaRevEffect::~CMonk_CycloneStrike_NovaRevEffect(void)
{
	Release();
}

void CMonk_CycloneStrike_NovaRevEffect::Initialize()
{
	CEffect::Initialize();

	m_pTransformCom->m_vSize = D3DXVECTOR3(1.f, 1.f, 1.f);
}

int CMonk_CycloneStrike_NovaRevEffect::Update()
{
	CEffect::Update();

	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();

	m_pTransformCom->m_vSize += D3DXVECTOR3(1.f, 1.f, 1.f) * 30.f * CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fTime >= 0.5f)
	{
		Destroy();
	}

	return 0;
}

void CMonk_CycloneStrike_NovaRevEffect::Render()
{
	CEffect::Render();
}

void CMonk_CycloneStrike_NovaRevEffect::Release()
{

}
