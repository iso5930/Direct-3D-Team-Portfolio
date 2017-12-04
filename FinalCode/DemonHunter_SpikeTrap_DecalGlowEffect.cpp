#include "StdAfx.h"
#include "DemonHunter_SpikeTrap_DecalGlowEffect.h"

CDemonHunter_SpikeTrap_DecalGlowEffect::CDemonHunter_SpikeTrap_DecalGlowEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner)
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
	CMaterialCom* pMaterialCom = new CMaterialCom(NULL, _T("Effect_Grenades_DecalGlow"));
	AddComponent(pMaterialCom);

	m_fTime = 0.f;
	m_iMode = 0;
}

CDemonHunter_SpikeTrap_DecalGlowEffect::~CDemonHunter_SpikeTrap_DecalGlowEffect(void)
{
	Release();
}

void CDemonHunter_SpikeTrap_DecalGlowEffect::Initialize()
{	
	CEffect::Initialize();

	m_pTransformCom->m_vSize = D3DXVECTOR3(250.f, 250.f, 250.f);
}

int CDemonHunter_SpikeTrap_DecalGlowEffect::Update()
{
	CEffect::Update();

	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fTime >= 10.f)
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

void CDemonHunter_SpikeTrap_DecalGlowEffect::Render()
{
	CEffect::Render();
}

void CDemonHunter_SpikeTrap_DecalGlowEffect::Release()
{

}

void CDemonHunter_SpikeTrap_DecalGlowEffect::Mode1()
{
	if(m_fAlpha <= 0.f)
	{
		++m_iMode;
	}

	m_fAlpha -= 0.5f * CTimeMgr::GetInstance()->GetDeltaTime();
}

void CDemonHunter_SpikeTrap_DecalGlowEffect::Mode2()
{
	if(m_fAlpha >= 0.2f)
	{
		--m_iMode;
	}

	m_fAlpha += 0.5f * CTimeMgr::GetInstance()->GetDeltaTime();
}
