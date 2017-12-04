#include "StdAfx.h"
#include "DemonHunter_Bola_AfterImageEffect.h"

CDemonHunter_Bola_AfterImageEffect::CDemonHunter_Bola_AfterImageEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner)
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
	pRenderCom->m_dwPass = 6;
	AddComponent(pRenderCom);

	// MaterialCom
	CMaterialCom* pMaterialCom = new CMaterialCom(NULL, _T("Effect_Bola_Arrow"));
	AddComponent(pMaterialCom);

	m_fTime = 0.f;
}

CDemonHunter_Bola_AfterImageEffect::~CDemonHunter_Bola_AfterImageEffect(void)
{
	Release();
}

void CDemonHunter_Bola_AfterImageEffect::Initialize()
{
	CEffect::Initialize();

	m_pTransformCom->m_vSize = D3DXVECTOR3(100.f, 100.f, 1.f);
}

int CDemonHunter_Bola_AfterImageEffect::Update()
{
	CEffect::Update();

	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();

	m_pTransformCom->m_vSize += D3DXVECTOR3(0.5f, 0.5f, 0.f) * 1000.f * CTimeMgr::GetInstance()->GetDeltaTime();
	m_pTransformCom->m_vAngle.y += D3DXToRadian(720.f) * CTimeMgr::GetInstance()->GetDeltaTime();

	m_fAlpha += 5.f * CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fTime >= 0.1f)
		Destroy();

	return 0;
}

void CDemonHunter_Bola_AfterImageEffect::Render()
{
	CEffect::Render();
}

void CDemonHunter_Bola_AfterImageEffect::Release()
{

}