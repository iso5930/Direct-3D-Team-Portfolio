#include "StdAfx.h"
#include "Monk_CripplingWave_Attack2TrailEffect.h"

CMonk_CripplingWave_Attack2TrailEffect::CMonk_CripplingWave_Attack2TrailEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXMATRIX* _pMatWorld)
:CTrailEffect(_tszObjKey, _eObjType, 50, _pMatWorld, &D3DXVECTOR3(0.f, 20.f, 0.f), &D3DXVECTOR3(0.f, -20.f, 0.f), 0.01f, _T("Effect_CripplingWave_Trail"))
{
	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_EFFECT);
	pRenderCom->m_dwPass = 2;
	AddComponent(pRenderCom);
}

CMonk_CripplingWave_Attack2TrailEffect::~CMonk_CripplingWave_Attack2TrailEffect(void)
{
	Release();
}

void CMonk_CripplingWave_Attack2TrailEffect::Initialize()
{
	CTrailEffect::Initialize();	
}

int CMonk_CripplingWave_Attack2TrailEffect::Update()
{
	CTrailEffect::Update();

	return 0;
}

void CMonk_CripplingWave_Attack2TrailEffect::Render()
{
	CTrailEffect::Render();
}

void CMonk_CripplingWave_Attack2TrailEffect::Release()
{
	
}