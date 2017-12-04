#include "StdAfx.h"
#include "Wizard_FrostNova_FrostEffect.h"

CWizard_FrostNova_FrostEffect::CWizard_FrostNova_FrostEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
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
	CMaterialCom* pMaterialCom = new CMaterialCom(NULL, _T("Effect_FrostNova"));
	AddComponent(pMaterialCom);

	// CollisionCom
	CCollisionCom* pCollisionCom = new CCollisionCom(COLL_TYPE_PLAYER_EFFECT, new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 200.0f), new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 200.0f));
	AddComponent(pCollisionCom);

	m_iMaxCnt = 100;

	m_fTime = 0.f;

	// Coef
	m_fCoef = 1.0f;
}

CWizard_FrostNova_FrostEffect::~CWizard_FrostNova_FrostEffect(void)
{
	Release();
}

void CWizard_FrostNova_FrostEffect::Initialize()
{
	CEffect::Initialize();

	m_pTransformCom->m_vSize = D3DXVECTOR3(100.f, 100.f, 1.f);
	m_pTransformCom->m_vAngle.x = D3DXToRadian(90.f);
}

int CWizard_FrostNova_FrostEffect::Update()
{
	CEffect::Update();

	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fTime >= 0.25f)
	{
		Destroy();
	}

	m_pTransformCom->m_vSize += D3DXVECTOR3(1.f, 1.f, 0.f) * 1500.f * CTimeMgr::GetInstance()->GetDeltaTime();

	return 0;
}

void CWizard_FrostNova_FrostEffect::Render()
{
	CEffect::Render();
}

void CWizard_FrostNova_FrostEffect::Release()
{

}
