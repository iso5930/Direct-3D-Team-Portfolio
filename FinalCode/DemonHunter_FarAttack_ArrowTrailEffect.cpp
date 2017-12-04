#include "StdAfx.h"
#include "DemonHunter_FarAttack_ArrowTrailEffect.h"

CDemonHunter_FarAttack_ArrowTrailEffect::CDemonHunter_FarAttack_ArrowTrailEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, D3DXMATRIX* _pMatrix)
: CTrailEffect(_tszObjKey, _eObjType, 50, _pMatrix, &D3DXVECTOR3(0.0f, 10.0f, 0.0f), &D3DXVECTOR3(0.0f, -10.0f, 0.0f), 0.01f, _T("Effect_ArrowTrail"))
{
	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_EFFECT);
	pRenderCom->m_dwPass = 1;
	AddComponent(pRenderCom);
}

CDemonHunter_FarAttack_ArrowTrailEffect::~CDemonHunter_FarAttack_ArrowTrailEffect()
{
	Release();
}

void CDemonHunter_FarAttack_ArrowTrailEffect::Initialize()
{
	CTrailEffect::Initialize();
}

int CDemonHunter_FarAttack_ArrowTrailEffect::Update()
{
	CTrailEffect::Update();

	return 0;
}

void CDemonHunter_FarAttack_ArrowTrailEffect::Render()
{
	CTrailEffect::Render();
}

void CDemonHunter_FarAttack_ArrowTrailEffect::Release()
{

}