#include "StdAfx.h"
#include "DemonHunter_EntanglingShot_ArrowDistortionEffect.h"

CDemonHunter_EntanglingShot_ArrowDistortionEffect::CDemonHunter_EntanglingShot_ArrowDistortionEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	//BufferCom
	CBufferCom* pBufferCom = new CBufferCom;
	pBufferCom->AddBuffer(_T("Effect_SlowTime"));
	AddComponent(pBufferCom);
	
	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_EFFECT);
	pRenderCom->m_dwPass = 13;
	AddComponent(pRenderCom);

	m_fTime = 0.0f;
}

CDemonHunter_EntanglingShot_ArrowDistortionEffect::~CDemonHunter_EntanglingShot_ArrowDistortionEffect(void)
{
	Release();
}

void CDemonHunter_EntanglingShot_ArrowDistortionEffect::Initialize()
{
	CEffect::Initialize();

	m_fAlpha = 0.9f;

	m_pTransformCom->m_vSize = D3DXVECTOR3(0.5f, 0.5f, 0.5f);
}

int CDemonHunter_EntanglingShot_ArrowDistortionEffect::Update()
{
	CEffect::Update();

	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();

	m_pTransformCom->m_vSize += D3DXVECTOR3(0.5f, 0.5f, 0.5f) * CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fTime >= 0.3f)
		Destroy();

	return 0;
} 

void CDemonHunter_EntanglingShot_ArrowDistortionEffect::Render()
{
	CEffect::Render();
}

void CDemonHunter_EntanglingShot_ArrowDistortionEffect::Release()
{

}