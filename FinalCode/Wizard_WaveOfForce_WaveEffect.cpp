#include "StdAfx.h"
#include "Wizard_WaveOfForce_WaveEffect.h"

CWizard_WaveOfForce_WaveEffect::CWizard_WaveOfForce_WaveEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	m_fTime = 0.f;

	// BufferCom
	CBufferCom* pBufferCom = new CBufferCom;
	pBufferCom->AddBuffer(_T("Effect_WaveOfForce"));
	AddComponent(pBufferCom);

	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_EFFECT);
	pRenderCom->m_dwPass = 17;
	AddComponent(pRenderCom);

	// MaterialCom
	CMaterialCom* pMaterialCom = new CMaterialCom(NULL, _T("Effect_waveOfForce_alpha"));
	AddComponent(pMaterialCom);

	// Coef
	m_fCoef = 3.9f;
}

CWizard_WaveOfForce_WaveEffect::~CWizard_WaveOfForce_WaveEffect(void)
{
	Release();
}

void CWizard_WaveOfForce_WaveEffect::Initialize()
{
	CEffect::Initialize();

	m_pTransformCom->m_vSize = D3DXVECTOR3(0.5f, 0.5f, 0.5f);
}

int CWizard_WaveOfForce_WaveEffect::Update()
{
	CEffect::Update();

	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();

	m_pTransformCom->m_vSize += D3DXVECTOR3(2.f, 2.f, 2.f) * 2.f * CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fTime >= 0.5f)
	{
		Destroy();
	}

	return 0;
}

void CWizard_WaveOfForce_WaveEffect::Render()
{
	CEffect::Render();
}

void CWizard_WaveOfForce_WaveEffect::Release()
{

}

void CWizard_WaveOfForce_WaveEffect::AddCCollision()
{
	// CollisionCom
	CCollisionCom* pCollisionCom = new CCollisionCom(COLL_TYPE_PLAYER_EFFECT, new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 400.f), new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 400.f));
	AddComponent(pCollisionCom);
	pCollisionCom->Initialize();

	m_iMaxCnt = 100;
}	
