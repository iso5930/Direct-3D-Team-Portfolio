#include "StdAfx.h"
#include "DemonHunter_ClusterArrow_TrailEffect.h"

CDemonHunter_ClusterArrow_TrailEffect::CDemonHunter_ClusterArrow_TrailEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXMATRIX* _pWorld, D3DXVECTOR3 _vDir)
:CTrailEffect_3(_tszObjKey, _eObjType, 50, _pWorld, &D3DXVECTOR3(0.f, 0.f, 50.f), &D3DXVECTOR3(0.f, 0.f, -50.f), 0.01f, _T("Effect_Cluster_Trail"), 2, _vDir)
{
	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_EFFECT);
	pRenderCom->m_dwPass = 2;
	AddComponent(pRenderCom);
}

CDemonHunter_ClusterArrow_TrailEffect::~CDemonHunter_ClusterArrow_TrailEffect(void)
{
	Release();
}

void CDemonHunter_ClusterArrow_TrailEffect::Initialize()
{
	CTrailEffect_3::Initialize();
}

int CDemonHunter_ClusterArrow_TrailEffect::Update()
{
	CTrailEffect_3::Update();

	return 0;
}

void CDemonHunter_ClusterArrow_TrailEffect::Render()
{
	CTrailEffect_3::Render();
}

void CDemonHunter_ClusterArrow_TrailEffect::Release()
{

}