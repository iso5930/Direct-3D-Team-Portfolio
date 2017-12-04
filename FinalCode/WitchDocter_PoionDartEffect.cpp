#include "StdAfx.h"
#include "WitchDocter_PoionDartEffect.h"

CWitchDocter_PoionDartEffect::CWitchDocter_PoionDartEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXVECTOR3* _pDir)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	m_vDir = *_pDir;

	// BufferCom
	CBufferCom* pBufferCom = new CBufferCom;
	pBufferCom->AddBuffer(_T("Effect_PoisonDart"));
	AddComponent(pBufferCom);

	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_EFFECT);
	pRenderCom->m_dwPass = 0;
	AddComponent(pRenderCom);

	// CollisionCom
	CCollisionCom* pCollisionCom = new CCollisionCom(COLL_TYPE_PLAYER_EFFECT, new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 20.0f), new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 20.0f));
	AddComponent(pCollisionCom);
}


CWitchDocter_PoionDartEffect::~CWitchDocter_PoionDartEffect(void)
{
	Release();
}

void CWitchDocter_PoionDartEffect::Initialize()
{
	CEffect::Initialize();

	m_pTrailEffect = new CWitchDocter_PoionDart_TrailEffect(NULL , OBJ_TYPE_DYNAMIC , 6 , &m_pTransformCom->m_mWorld ,	D3DXVECTOR3(0.0f , 5.f , -30.0f ), D3DXVECTOR3(0.0f , -5.f , -30.0f ) , 0.05f , _T("Effect_Trail_Poison") , 2 );
	m_pLayer->AddObject(m_pTrailEffect, LAYER_TYPE_EFFECT);
	m_pTrailEffect->Initialize();
}

int CWitchDocter_PoionDartEffect::Update()
{
	CEffect::Update();

	if(CCameraMgr::GetInstance()->IsIn(&m_pTransformCom->m_vPos, 500.0f) == false)
		Destroy();

	m_pTransformCom->m_vPos += m_vDir * CTimeMgr::GetInstance()->GetDeltaTime() * 1000.f;

	return 0;
}

void CWitchDocter_PoionDartEffect::Render()
{
	CEffect::Render();
}

void CWitchDocter_PoionDartEffect::Release()
{
	if(m_pTrailEffect != NULL)
	{
		m_pTrailEffect->Destroy();
		m_pTrailEffect = NULL;
	}

}
