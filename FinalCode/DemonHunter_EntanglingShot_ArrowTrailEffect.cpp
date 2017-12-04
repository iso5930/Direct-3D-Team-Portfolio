#include "StdAfx.h"
#include "DemonHunter_EntanglingShot_ArrowTrailEffect.h"

CDemonHunter_EntanglingShot_ArrowTrailEffect::CDemonHunter_EntanglingShot_ArrowTrailEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, D3DXMATRIX* _pMatrix)
: CTrailEffect_2(_tszObjKey, _eObjType, 50, _pMatrix, &D3DXVECTOR3(0.0f, 10.0f, 0.0f), &D3DXVECTOR3(0.0f, -10.0f, 0.0f), 0.01f, _T("Effect_EntangleShot_Trail"))
{
	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_EFFECT);
	pRenderCom->m_dwPass = 2;
	AddComponent(pRenderCom);
}

CDemonHunter_EntanglingShot_ArrowTrailEffect::~CDemonHunter_EntanglingShot_ArrowTrailEffect(void)
{
	Release();
}

void CDemonHunter_EntanglingShot_ArrowTrailEffect::Initialize()
{
	CTrailEffect_2::Initialize();
}

int CDemonHunter_EntanglingShot_ArrowTrailEffect::Update()
{
	CTrailEffect_2::Update();

	return 0;
}

void CDemonHunter_EntanglingShot_ArrowTrailEffect::Render()
{
	CTrailEffect_2::Render();
}

void CDemonHunter_EntanglingShot_ArrowTrailEffect::Release()
{
	
}