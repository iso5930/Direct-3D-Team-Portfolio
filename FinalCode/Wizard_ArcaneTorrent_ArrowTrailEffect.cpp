#include "StdAfx.h"
#include "Wizard_ArcaneTorrent_ArrowTrailEffect.h"

CWizard_ArcaneTorrent_ArrowTrailEffect::CWizard_ArcaneTorrent_ArrowTrailEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, D3DXMATRIX* _pMatrix)
:CTrailEffect_2(_tszObjKey, _eObjType, 10, _pMatrix, &D3DXVECTOR3(0.f, 2.f, 0.f), &D3DXVECTOR3(0.f, -2.f, 0.f), 0.01f, _T("Effect_ArcaneTorrent_ArrowTrail"))
{
	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_EFFECT);
	pRenderCom->m_dwPass = 2;
	AddComponent(pRenderCom);
}

CWizard_ArcaneTorrent_ArrowTrailEffect::~CWizard_ArcaneTorrent_ArrowTrailEffect(void)
{
	Release();
}

void CWizard_ArcaneTorrent_ArrowTrailEffect::Initialize()
{
	CTrailEffect_2::Initialize();
}

int CWizard_ArcaneTorrent_ArrowTrailEffect::Update()
{
	CTrailEffect_2::Update();

	return 0;
}

void CWizard_ArcaneTorrent_ArrowTrailEffect::Render()
{
	CTrailEffect_2::Render();
}

void CWizard_ArcaneTorrent_ArrowTrailEffect::Release()
{

}
