#include "StdAfx.h"
#include "DemonHunter_SmokeScreen_FlashEffect.h"

CDemonHunter_SmokeScreen_FlashEffect::CDemonHunter_SmokeScreen_FlashEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXVECTOR3* _pDir)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	m_vDir = (*_pDir);
	m_fTime = 0.f;
	m_iMode = 0;

	// BufferCom
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
	CMaterialCom* pMaterialCom = new CMaterialCom(NULL, _T("Effect_SmokeScreen_Flash"));
	AddComponent(pMaterialCom);
}

CDemonHunter_SmokeScreen_FlashEffect::~CDemonHunter_SmokeScreen_FlashEffect(void)
{
	Release();
}

void CDemonHunter_SmokeScreen_FlashEffect::Initialize()
{
	CEffect::Initialize();

	m_pTransformCom->m_vSize = D3DXVECTOR3(1.f, 1.f, 1.f);
}

int CDemonHunter_SmokeScreen_FlashEffect::Update()
{	
	CEffect::Update();
	
	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();
	m_pTransformCom->m_vPos += m_vDir * CTimeMgr::GetInstance()->GetDeltaTime();

	switch(m_iMode)
	{
	case 0:
		Mode1();
		break;

	case 1:
		Mode2();
		break;
	}

	return 0;
}		

void CDemonHunter_SmokeScreen_FlashEffect::Render()
{
	CEffect::Render();
}

void CDemonHunter_SmokeScreen_FlashEffect::Release()
{

}

void CDemonHunter_SmokeScreen_FlashEffect::Mode1()
{
	m_pTransformCom->m_vSize += D3DXVECTOR3(0.5f, 0.5f, 0.f) * 1000.f * CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fTime >= 0.1f)
	{
		++m_iMode;
	}
}

void CDemonHunter_SmokeScreen_FlashEffect::Mode2()
{
	m_pTransformCom->m_vSize -= D3DXVECTOR3(0.5f, 0.5f, 0.f) * 500.f * CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fTime >= 0.1f)
	{
		Destroy();
	}
}