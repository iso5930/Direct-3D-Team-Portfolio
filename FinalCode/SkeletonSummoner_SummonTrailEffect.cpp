#include "StdAfx.h"
#include "SkeletonSummoner_SummonTrailEffect.h"

CSkeletonSummoner_SummonTrailEffect::CSkeletonSummoner_SummonTrailEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, D3DXMATRIX* _pMatrix)
: CTrailEffect_2(_tszObjKey, _eObjType, 200, _pMatrix, &D3DXVECTOR3(50.f, 0.f, 0.f), &D3DXVECTOR3(-50.f, 0.f, 0.f), 0.01f, _T("SkeletonSummoner_TrailEffect"))
{
	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_EFFECT);
	pRenderCom->m_dwPass = 2;
	AddComponent(pRenderCom);
}

CSkeletonSummoner_SummonTrailEffect::~CSkeletonSummoner_SummonTrailEffect(void)
{
	Release();
}

void CSkeletonSummoner_SummonTrailEffect::Initialize()
{
	CTrailEffect_2::Initialize();
}

int CSkeletonSummoner_SummonTrailEffect::Update()
{
	CTrailEffect_2::Update();

	return 0;
}

void CSkeletonSummoner_SummonTrailEffect::Render()
{
	CTrailEffect_2::Render();
}

void CSkeletonSummoner_SummonTrailEffect::Release()
{

}
