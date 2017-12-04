#include "StdAfx.h"
#include "DemonHunter_RainOfVengeance_ArrowEffect.h"

CDemonHunter_RainOfVengeance_ArrowEffect::CDemonHunter_RainOfVengeance_ArrowEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXVECTOR3* _pDir)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	//Dir 
	m_vDir = *_pDir;

	// BufferCom
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
	CMaterialCom* pMaterialCom = new CMaterialCom(NULL, _T("Effect_RainOfVengeance_Arrow"));
	AddComponent(pMaterialCom);

	m_fTime = 0.f;

	// Coef
	m_fCoef = 3.0f;
}

CDemonHunter_RainOfVengeance_ArrowEffect::~CDemonHunter_RainOfVengeance_ArrowEffect(void)
{
	Release();
}	

void CDemonHunter_RainOfVengeance_ArrowEffect::Initialize()
{
	CEffect::Initialize();

	m_pTransformCom->m_vSize = D3DXVECTOR3(70.f, 10.f, 10.f);
	m_pTransformCom->m_vAngle.y = D3DXToRadian(-45.f);
}

int CDemonHunter_RainOfVengeance_ArrowEffect::Update()
{
	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();

	if(CCameraMgr::GetInstance()->IsIn(&m_pTransformCom->m_vPos, 500.0f) == false)
		Destroy();

	m_pTransformCom->m_vPos += m_vDir * CTimeMgr::GetInstance()->GetDeltaTime();

	CEffect::Update();

	return 0;
}

void CDemonHunter_RainOfVengeance_ArrowEffect::Render()
{	
	CEffect::Render();
}

void CDemonHunter_RainOfVengeance_ArrowEffect::Release()
{
}

void CDemonHunter_RainOfVengeance_ArrowEffect::AddCCollision()
{
	// CollisionCom
	CCollisionCom* pCollisionCom = new CCollisionCom(COLL_TYPE_PLAYER_EFFECT, new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 20.0f), new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 20.0f));
	AddComponent(pCollisionCom);
	pCollisionCom->Initialize();
}