#include "StdAfx.h"
#include "Butcher_AxeTrail.h"

CButcher_AxeTrail::CButcher_AxeTrail(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, D3DXMATRIX* _pMatrix)
: CTrailEffect(_tszObjKey, _eObjType, 50, _pMatrix, &D3DXVECTOR3(-100.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.01f, _T("Butcher_AxeTrail"))
{
	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_EFFECT);
	pRenderCom->m_dwPass = 2;
	AddComponent(pRenderCom);

}

CButcher_AxeTrail::~CButcher_AxeTrail(void)
{
	Release();
}

void CButcher_AxeTrail::Initialize()
{
	CTrailEffect::Initialize();
}

int CButcher_AxeTrail::Update()
{
	CTrailEffect::Update();

	return 0;
}

void CButcher_AxeTrail::Render()
{
	CTrailEffect::Render();
}

void CButcher_AxeTrail::Release()
{

}
