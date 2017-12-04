#include "StdAfx.h"
#include "Wizard_Hydra_FireBallEffect.h"

CWizard_Hydra_FireBallEffect::CWizard_Hydra_FireBallEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXVECTOR3 _vDir)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	// BufferCom
	CBufferCom* pBufferCom = new CBufferCom;
	pBufferCom->AddBuffer(_T("Effect_Hydra_FireBall"));
	AddComponent(pBufferCom);

	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_EFFECT);
	pRenderCom->m_dwPass = 0;
	AddComponent(pRenderCom);

	// CollisionCom
	CCollisionCom* pCollisionCom = new CCollisionCom(COLL_TYPE_PLAYER_EFFECT, new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f), new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f));
	AddComponent(pCollisionCom);

	m_vDir = _vDir;

	// Coef
	m_fCoef = 1.65f;
}

CWizard_Hydra_FireBallEffect::~CWizard_Hydra_FireBallEffect(void)
{
	Release();
}

void CWizard_Hydra_FireBallEffect::Initialize()
{
	CEffect::Initialize();
}

int CWizard_Hydra_FireBallEffect::Update()
{
	CEffect::Update();

	if(CCameraMgr::GetInstance()->IsIn(&m_pTransformCom->m_vPos, 500.0f) == false)
		Destroy();

	m_pTransformCom->m_vPos += m_vDir * CTimeMgr::GetInstance()->GetDeltaTime();

	return 0;
}

void CWizard_Hydra_FireBallEffect::Render()
{
	CEffect::Render();
}

void CWizard_Hydra_FireBallEffect::Release()
{

}
