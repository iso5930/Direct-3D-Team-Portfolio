#include "StdAfx.h"
#include "DemonHunter_Sentry_BaseEffect.h"

CDemonHunter_Sentry_BaseEffect::CDemonHunter_Sentry_BaseEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXMATRIX* _pWorld)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	m_pWorld = _pWorld;

	// BufferCom
	CBufferCom* pBufferCom = new CBufferCom;
	pBufferCom->AddBuffer(_T("Effect_Sentry_Base"));
	AddComponent(pBufferCom);

	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_EFFECT);
	pRenderCom->m_dwPass = 0;
	AddComponent(pRenderCom);
}

CDemonHunter_Sentry_BaseEffect::~CDemonHunter_Sentry_BaseEffect(void)
{
	Release();
}

void CDemonHunter_Sentry_BaseEffect::Initialize()
{
	CEffect::Initialize();
}

int CDemonHunter_Sentry_BaseEffect::Update()
{
	CEffect::Update();

	m_pTransformCom->m_mWorld *= (*m_pWorld);

	return 0;
}

void CDemonHunter_Sentry_BaseEffect::Render()
{
	CEffect::Render();
}

void CDemonHunter_Sentry_BaseEffect::Release()
{

}
