#include "StdAfx.h"
#include "DemonHunter_HungeringArrow_AfterImageEffect.h"

CDemonHunter_HungeringArrow_AfterImageEffect::CDemonHunter_HungeringArrow_AfterImageEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	//BufferCom
	CBufferCom* pBufferCom = new CBufferCom;
	pBufferCom->AddBuffer(_T("Rect"));
	AddComponent(pBufferCom);

	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_EFFECT);
	pRenderCom->m_dwPass = 3;
	AddComponent(pRenderCom);

	// MaterialCom
	CMaterialCom* pMaterialCom = new CMaterialCom(NULL, _T("Effect_HungeringArrow_Trail"));
	AddComponent(pMaterialCom);

	m_fTime = 0.f;
}

CDemonHunter_HungeringArrow_AfterImageEffect::~CDemonHunter_HungeringArrow_AfterImageEffect(void)
{
	Release();
}

void CDemonHunter_HungeringArrow_AfterImageEffect::Initialize()
{
	CEffect::Initialize();

	m_pTransformCom->m_vSize = D3DXVECTOR3(50.f, 25.f, 25.f);
}

int CDemonHunter_HungeringArrow_AfterImageEffect::Update()
{
	CEffect::Update();

	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();

	m_pTransformCom->m_vSize -= D3DXVECTOR3(2.f, 1.f, 1.f) * 100.f * CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_pTransformCom->m_vSize.z <= 0.f)
		Destroy();

	return 0;
}

void CDemonHunter_HungeringArrow_AfterImageEffect::Render()
{	
	CEffect::Render();
}

void CDemonHunter_HungeringArrow_AfterImageEffect::Release()
{
	
}