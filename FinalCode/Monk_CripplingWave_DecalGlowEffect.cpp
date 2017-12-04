#include "StdAfx.h"
#include "Monk_CripplingWave_DecalGlowEffect.h"

CMonk_CripplingWave_DecalGlowEffect::CMonk_CripplingWave_DecalGlowEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	//BufferCom
	CBufferCom* pBufferCom = new CBufferCom;
	pBufferCom->AddBuffer(_T("Cube"));
	AddComponent(pBufferCom);

	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	// RenderCom
	CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_EFFECT);
	pRenderCom->m_dwPass = 7; //µ¥Ä®
	AddComponent(pRenderCom);

	// MaterialCom
	CMaterialCom* pMaterialCom = new CMaterialCom(NULL, _T("Effect_CripplingWave_DecalGlow"));
	AddComponent(pMaterialCom);

	m_fTime = 0.f;
}

CMonk_CripplingWave_DecalGlowEffect::~CMonk_CripplingWave_DecalGlowEffect(void)
{
	Release();
}

void CMonk_CripplingWave_DecalGlowEffect::Initialize()
{
	CEffect::Initialize();

	m_fAlpha = 0.4f;

	m_pTransformCom->m_vSize = D3DXVECTOR3(300.f, 300.f, 300.f);
}

int CMonk_CripplingWave_DecalGlowEffect::Update()
{
	CEffect::Update();

	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fTime >= 0.5f)
	{
		Destroy();
	}

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

void CMonk_CripplingWave_DecalGlowEffect::Render()
{
	CEffect::Render();
}

void CMonk_CripplingWave_DecalGlowEffect::Release()
{

}

void CMonk_CripplingWave_DecalGlowEffect::Mode1()
{
	if(m_fAlpha <= 0.f)
	{
		++m_iMode;
	}

	m_fAlpha -= 1.5f * CTimeMgr::GetInstance()->GetDeltaTime();
}

void CMonk_CripplingWave_DecalGlowEffect::Mode2()
{
	if(m_fAlpha >= 0.4f)
	{
		--m_iMode;
	}

	m_fAlpha += 1.5f * CTimeMgr::GetInstance()->GetDeltaTime();
}	