#include "StdAfx.h"
#include "DemonHunter_Impale_KnivesTrailEffect.h"

CDemonHunter_Impale_KnivesTrailEffect::CDemonHunter_Impale_KnivesTrailEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, D3DXMATRIX* _pMatrix)
:CTrailEffect(_tszObjKey, _eObjType, 30, _pMatrix, &D3DXVECTOR3(0.0f, 15.f, 0.0f), &D3DXVECTOR3(0.0f, -15.f, 0.0f), 0.01f, _T("Effect_Impale_Trail"))
{
	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_EFFECT);
	pRenderCom->m_dwPass = 2;
	AddComponent(pRenderCom);
}

CDemonHunter_Impale_KnivesTrailEffect::~CDemonHunter_Impale_KnivesTrailEffect(void)
{
	Release();
}

void CDemonHunter_Impale_KnivesTrailEffect::Initialize()
{
	CTrailEffect::Initialize();
}

int CDemonHunter_Impale_KnivesTrailEffect::Update()
{	
	CTrailEffect::Update();

	return 0;
}

void CDemonHunter_Impale_KnivesTrailEffect::Render()
{	
	CTrailEffect::Render();
}

void CDemonHunter_Impale_KnivesTrailEffect::Release()
{

}