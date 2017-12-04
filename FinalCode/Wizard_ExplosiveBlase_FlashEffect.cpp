#include "StdAfx.h"
#include "Wizard_ExplosiveBlase_FlashEffect.h"

CWizard_ExplosiveBlase_FlashEffect::CWizard_ExplosiveBlase_FlashEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	// BufferCom
	CBufferCom* pBufferCom = new CBufferCom;
	pBufferCom->AddBuffer(_T("Effect_ExplosiveBlast"));
	AddComponent(pBufferCom);

	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_EFFECT);
	pRenderCom->m_dwPass = 0;
	AddComponent(pRenderCom);

	// CollisionCom
	CCollisionCom* pCollisionCom = new CCollisionCom(COLL_TYPE_PLAYER_EFFECT, new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 200.0f), new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 200.0f));
	AddComponent(pCollisionCom);

	m_iMaxCnt = 100;

	m_fTime = 0.f;

	// Coef
	m_fCoef = 9.45f;
}

CWizard_ExplosiveBlase_FlashEffect::~CWizard_ExplosiveBlase_FlashEffect(void)
{
	Release();
}

void CWizard_ExplosiveBlase_FlashEffect::Initialize()
{
	CEffect::Initialize();

	m_pTransformCom->m_vSize = D3DXVECTOR3(0.5f, 0.5f, 0.5f);
}

int CWizard_ExplosiveBlase_FlashEffect::Update()
{
	CEffect::Update();

	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();

	m_pTransformCom->m_vSize += D3DXVECTOR3(2.f, 2.f, 2.f) * 2.f * CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fTime >= 0.3f)
	{
		Destroy();
	}

	return 0;
}

void CWizard_ExplosiveBlase_FlashEffect::Render()
{
	CEffect::Render();
}

void CWizard_ExplosiveBlase_FlashEffect::Release()
{

}
