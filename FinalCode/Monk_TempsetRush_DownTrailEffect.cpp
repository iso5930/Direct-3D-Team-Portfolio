#include "StdAfx.h"
#include "Monk_TempsetRush_DownTrailEffect.h"

CMonk_TempsetRush_DownTrailEffect::CMonk_TempsetRush_DownTrailEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, D3DXMATRIX* _pWorld)
:CTrailEffect(_tszObjKey, OBJ_TYPE_DYNAMIC, 30, _pWorld, &D3DXVECTOR3(10.f, -50.f, 0.f), &D3DXVECTOR3(-10.f, -50.f, 0.f), 0.01f, _T("Effect_CripplingWave_Trail"))

{
	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_EFFECT);
	pRenderCom->m_dwPass = 2;
	AddComponent(pRenderCom);
}

CMonk_TempsetRush_DownTrailEffect::~CMonk_TempsetRush_DownTrailEffect(void)
{
	Release();
}

void CMonk_TempsetRush_DownTrailEffect::Initialize()
{
	CTrailEffect::Initialize();
}

int CMonk_TempsetRush_DownTrailEffect::Update()
{
	CTrailEffect::Update();

	return 0;
}

void CMonk_TempsetRush_DownTrailEffect::Render()
{
	CTrailEffect::Render();
}

void CMonk_TempsetRush_DownTrailEffect::Release()
{

}
