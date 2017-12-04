#include "StdAfx.h"
#include "Monk_SevenSidedStrike_DecalGlowEffect.h"

CMonk_SevenSidedStrike_DecalGlowEffect::CMonk_SevenSidedStrike_DecalGlowEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner)
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
	CMaterialCom* pMaterialCom = new CMaterialCom(NULL, _T("Effect_SevenSidedStrike_DecalGlow"));
	AddComponent(pMaterialCom);

	m_iMode = 0;
	m_fTime = 0.f;
	m_fAccTime = 0.f; 
}

CMonk_SevenSidedStrike_DecalGlowEffect::~CMonk_SevenSidedStrike_DecalGlowEffect(void)
{
	Release();
}

void CMonk_SevenSidedStrike_DecalGlowEffect::Initialize()
{
	CEffect::Initialize();

	m_pTransformCom->m_vSize = D3DXVECTOR3(350.f, 350.f, 350.f);
}

int CMonk_SevenSidedStrike_DecalGlowEffect::Update()
{
	CEffect::Update();

	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();
	m_fAccTime += CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fAccTime >= 2.2f)
		Destroy();

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

void CMonk_SevenSidedStrike_DecalGlowEffect::Render()
{
	CEffect::Render();
}

void CMonk_SevenSidedStrike_DecalGlowEffect::Release()
{

}

void CMonk_SevenSidedStrike_DecalGlowEffect::Mode1()
{
	if(m_fAlpha >= 0.5f)
		++m_iMode;

	m_fAlpha += 1.f * CTimeMgr::GetInstance()->GetDeltaTime();
}

void CMonk_SevenSidedStrike_DecalGlowEffect::Mode2()
{
	if(m_fAlpha <= 0.f)
		--m_iMode;

	m_fAlpha -= 1.f * CTimeMgr::GetInstance()->GetDeltaTime();
}
