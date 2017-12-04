#include "StdAfx.h"
#include "Monk_WaveOfLigth_BellDestoryEffect.h"

CMonk_WaveOfLigth_BellDestoryEffect::CMonk_WaveOfLigth_BellDestoryEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	// BufferCom
	CBufferCom* pBufferCom = new CBufferCom;
	pBufferCom->AddBuffer(_T("Effect_WaveOfLight_Destroy"));
	AddComponent(pBufferCom);

	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_EFFECT);
	pRenderCom->m_dwPass = 14;
	AddComponent(pRenderCom);

	// CollisionCom
	CCollisionCom* pCollisionCom = new CCollisionCom(COLL_TYPE_PLAYER_EFFECT, new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 80.f), new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 80.f));
	AddComponent(pCollisionCom);

	m_iMaxCnt = 100;

	m_fAlpha = 0.5f;

	// Coef
	m_fCoef = 6.35f;
}

CMonk_WaveOfLigth_BellDestoryEffect::~CMonk_WaveOfLigth_BellDestoryEffect(void)
{
	Release();
}

void CMonk_WaveOfLigth_BellDestoryEffect::Initialize()
{
	CEffect::Initialize();
}

int CMonk_WaveOfLigth_BellDestoryEffect::Update()
{
	CEffect::Update();
	
	m_fAlpha += 0.4f * CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fAlpha >= 1.f)
		Destroy();

	return 0;
}

void CMonk_WaveOfLigth_BellDestoryEffect::Render()
{
	CEffect::Render();
}

void CMonk_WaveOfLigth_BellDestoryEffect::Release()
{

}
