#include "StdAfx.h"
#include "Monk_TempsetRush_TrailEffect.h"

CMonk_TempsetRush_TrailEffect::CMonk_TempsetRush_TrailEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, D3DXMATRIX* _pWorld)
:CTrailEffect(_tszObjKey, OBJ_TYPE_DYNAMIC, 30, _pWorld, &D3DXVECTOR3(10.f, 50.f, 0.f), &D3DXVECTOR3(-10.f, 50.f, 0.f), 0.01f, _T("Effect_CripplingWave_Trail"))
{
	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_EFFECT);
	pRenderCom->m_dwPass = 2;
	AddComponent(pRenderCom);
}
	
CMonk_TempsetRush_TrailEffect::~CMonk_TempsetRush_TrailEffect(void)
{
	Release();
}

void CMonk_TempsetRush_TrailEffect::Initialize()
{
	CTrailEffect::Initialize();
}

int CMonk_TempsetRush_TrailEffect::Update()
{
	CTrailEffect::Update();

	return 0;
}

void CMonk_TempsetRush_TrailEffect::Render()
{
	CTrailEffect::Render();
}

void CMonk_TempsetRush_TrailEffect::Release()
{

}
