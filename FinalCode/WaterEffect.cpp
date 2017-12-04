#include "StdAfx.h"
#include "WaterEffect.h"

CWaterEffect::CWaterEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, float _fSpeedX, float _fSpeedY, TCHAR* _tszName, float _fDetail)
:CEffect(_tszObjKey, _eObjType, NULL)
{
	// Speed
	m_fSpeedX = _fSpeedX;
	m_fSpeedY = _fSpeedY;

	// Detail
	m_fDetail = _fDetail;

	// BufferCom
	CBufferCom* pBufferCom = new CBufferCom;
	pBufferCom->AddBuffer(_tszName);
	AddComponent(pBufferCom);

	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_EFFECT);
	pRenderCom->m_dwPass = 22;
	AddComponent(pRenderCom);

	m_bCheck = false;
}

CWaterEffect::~CWaterEffect(void)
{
	Release();
}

void CWaterEffect::Initialize()
{
	CEffect::Initialize();
}

int CWaterEffect::Update()
{
	CEffect::Update();
	
	return 0;
}

void CWaterEffect::Render()
{
	CEffect::Render();
}

void CWaterEffect::Release()
{

}