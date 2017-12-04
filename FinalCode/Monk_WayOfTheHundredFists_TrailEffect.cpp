#include "StdAfx.h"
#include "Monk_WayOfTheHundredFists_TrailEffect.h"

CMonk_WayOfTheHundredFists_TrailEffect::CMonk_WayOfTheHundredFists_TrailEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXMATRIX* _pMatWorld)
:CTrailEffect(_tszObjKey, _eObjType, 30, _pMatWorld, &D3DXVECTOR3(0.f, 20.f, 0.f), &D3DXVECTOR3(0.f, -20.f, 0.f), 0.01f, _T("Effect_DeadlyReach_Trail"))
{
	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_EFFECT);
	pRenderCom->m_dwPass = 2;
	AddComponent(pRenderCom);
}

CMonk_WayOfTheHundredFists_TrailEffect::~CMonk_WayOfTheHundredFists_TrailEffect(void)
{
	Release();
}

void CMonk_WayOfTheHundredFists_TrailEffect::Initialize()
{
	CTrailEffect::Initialize();
}

int CMonk_WayOfTheHundredFists_TrailEffect::Update()
{
	CTrailEffect::Update();

	return 0;
}

void CMonk_WayOfTheHundredFists_TrailEffect::Render()
{
	CTrailEffect::Render();
}

void CMonk_WayOfTheHundredFists_TrailEffect::Release()
{

}
