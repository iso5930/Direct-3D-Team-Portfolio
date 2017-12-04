#include "StdAfx.h"
#include "Monk_BlindingFlash_FlashEffect.h"

CMonk_BlindingFlash_FlashEffect::CMonk_BlindingFlash_FlashEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner)
:CEffect(_tszObjKey, OBJ_TYPE_DYNAMIC, _pOwner)
{
	// BufferCom
	CBufferCom* pBufferCom = new CBufferCom;
	pBufferCom->AddBuffer(_T("Effect_BlindingFlash"));
	AddComponent(pBufferCom);

	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_EFFECT);
	pRenderCom->m_dwPass = 19;
	AddComponent(pRenderCom);

	m_fAlpha = 1.f;
	m_iMode = 0;
	m_fTime = 0.f;
}

CMonk_BlindingFlash_FlashEffect::~CMonk_BlindingFlash_FlashEffect(void)
{
	Release();
}

void CMonk_BlindingFlash_FlashEffect::Initialize()
{
	CEffect::Initialize();
}

int CMonk_BlindingFlash_FlashEffect::Update()
{
	CEffect::Update();
	
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

void CMonk_BlindingFlash_FlashEffect::Render()
{
	CEffect::Render();
}

void CMonk_BlindingFlash_FlashEffect::Release()
{

}

void CMonk_BlindingFlash_FlashEffect::Mode1()
{
	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fTime >= 0.3f)
	{
		m_fAlpha = 0.f;
		++m_iMode;
	}
}

void CMonk_BlindingFlash_FlashEffect::Mode2()
{
	m_fAlpha += 3.f * CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fAlpha >= 1.f)
	{
		Destroy();
	}
}