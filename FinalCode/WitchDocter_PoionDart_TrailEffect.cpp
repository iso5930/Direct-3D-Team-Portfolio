#include "StdAfx.h"
#include "WitchDocter_PoionDart_TrailEffect.h"

CWitchDocter_PoionDart_TrailEffect::CWitchDocter_PoionDart_TrailEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType , int _iTrailNum , D3DXMATRIX* _pMatrix , D3DXVECTOR3& vUp ,  D3DXVECTOR3& vDown , float _fTrailInv , TCHAR* _tszTrailName, int _iPass)
: CTrailEffect(_tszObjKey, _eObjType, _iTrailNum , _pMatrix, &vUp, &vDown, _fTrailInv, _tszTrailName)
{
	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_EFFECT);
	pRenderCom->m_dwPass = _iPass;
	AddComponent(pRenderCom);
}

CWitchDocter_PoionDart_TrailEffect::~CWitchDocter_PoionDart_TrailEffect(void)
{
	
}

void CWitchDocter_PoionDart_TrailEffect::Initialize()
{
	CTrailEffect::Initialize();
}

int CWitchDocter_PoionDart_TrailEffect::Update()
{
	CTrailEffect::Update();

	return 0;
}

void CWitchDocter_PoionDart_TrailEffect::Render()
{
	CTrailEffect::Render();
}

void CWitchDocter_PoionDart_TrailEffect::Release()
{
	
}