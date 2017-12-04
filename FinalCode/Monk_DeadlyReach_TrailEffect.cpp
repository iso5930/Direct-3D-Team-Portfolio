#include "StdAfx.h"
#include "Monk_DeadlyReach_TrailEffect.h"

CMonk_DeadlyReach_TrailEffect::CMonk_DeadlyReach_TrailEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, D3DXMATRIX* _pMatrix)
:CTrailEffect(_tszObjKey, _eObjType, 26, _pMatrix, &D3DXVECTOR3(0.f, 15.f, 0.f), &D3DXVECTOR3(0.f, -15.f, 0.f), 0.01f, _T("Effect_DeadlyReach_Trail"))
{
	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_EFFECT);
	pRenderCom->m_dwPass = 2;
	AddComponent(pRenderCom);
}

CMonk_DeadlyReach_TrailEffect::~CMonk_DeadlyReach_TrailEffect(void)
{
	
}

void CMonk_DeadlyReach_TrailEffect::Initialize()
{
	CTrailEffect::Initialize();
}

int CMonk_DeadlyReach_TrailEffect::Update()
{
	CTrailEffect::Update();

	return 0;
}

void CMonk_DeadlyReach_TrailEffect::Render()
{	
	CTrailEffect::Render();
}

void CMonk_DeadlyReach_TrailEffect::Release()
{

}
