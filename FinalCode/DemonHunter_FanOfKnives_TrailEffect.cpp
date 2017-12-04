#include "StdAfx.h"
#include "DemonHunter_FanOfKnives_TrailEffect.h"

CDemonHunter_FanOfKnives_TrailEffect::CDemonHunter_FanOfKnives_TrailEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, D3DXMATRIX* _pMatrix)
: CTrailEffect(_tszObjKey, _eObjType, 50, _pMatrix, &D3DXVECTOR3(0.0f, 5.0f, 0.0f), &D3DXVECTOR3(0.0f, -5.0f, 0.0f), 0.01f, _T("Effect_ArrowTrail"))
{
	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_EFFECT);
	pRenderCom->m_dwPass = 1;
	AddComponent(pRenderCom);
}

CDemonHunter_FanOfKnives_TrailEffect::~CDemonHunter_FanOfKnives_TrailEffect(void)
{
	Release();
}

void CDemonHunter_FanOfKnives_TrailEffect::Initialize()
{
	CTrailEffect::Initialize();
}

int CDemonHunter_FanOfKnives_TrailEffect::Update()
{
	CTrailEffect::Update();

	return 0;
}

void CDemonHunter_FanOfKnives_TrailEffect::Render()
{
	CTrailEffect::Render();
}

void CDemonHunter_FanOfKnives_TrailEffect::Release()
{

}