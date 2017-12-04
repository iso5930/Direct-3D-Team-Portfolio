#include "StdAfx.h"
#include "Monk_LashingTailKick_KickEffect.h"

CMonk_LashingTailKick_KickEffect::CMonk_LashingTailKick_KickEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXVECTOR3 _vDir)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	m_vDir = _vDir;
	m_fTime = 0.f;

	//BufferCom
	CBufferCom* pBufferCom = new CBufferCom;
	pBufferCom->AddBuffer(_T("Rect"));
	AddComponent(pBufferCom);

	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_EFFECT);
	pRenderCom->m_dwPass = 3;
	AddComponent(pRenderCom);

	// MaterialCom
	CMaterialCom* pMaterialCom = new CMaterialCom(NULL, _T("Effect_LashingTailKick"));
	AddComponent(pMaterialCom);

	// CollisionCom
	CCollisionCom* pCollisionCom = new CCollisionCom(COLL_TYPE_PLAYER_EFFECT, new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100.f), new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100.f));
	AddComponent(pCollisionCom);

	m_iMaxCnt = 100;

	// Coef
	m_fCoef = 7.55f;
}

CMonk_LashingTailKick_KickEffect::~CMonk_LashingTailKick_KickEffect(void)
{
	Release();
}

void CMonk_LashingTailKick_KickEffect::Initialize()
{
	CEffect::Initialize();

	m_pTransformCom->m_vSize = D3DXVECTOR3(400.f, 200.f, 1.f);
	m_pTransformCom->m_vAngle.x = D3DXToRadian(-90.f);

	m_fAlpha = 0.1f;
}

int CMonk_LashingTailKick_KickEffect::Update()
{		
	CEffect::Update();
	
	m_pTransformCom->m_vPos += m_vDir * CTimeMgr::GetInstance()->GetDeltaTime();

	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fTime >= 0.5f)
		Destroy();

	return 0;
}

void CMonk_LashingTailKick_KickEffect::Render()
{
	CEffect::Render();
}

void CMonk_LashingTailKick_KickEffect::Release()
{

}
