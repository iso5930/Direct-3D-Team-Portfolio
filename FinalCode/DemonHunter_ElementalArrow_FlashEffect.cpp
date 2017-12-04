#include "StdAfx.h"
#include "DemonHunter_ElementalArrow_FlashEffect.h"

CDemonHunter_ElementalArrow_FlashEffect::CDemonHunter_ElementalArrow_FlashEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXMATRIX* _pWorld)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	m_pWorld = _pWorld;

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
	CMaterialCom* pMaterialCom = new CMaterialCom(NULL, _T("Effect_Elemental_Flash"));
	AddComponent(pMaterialCom);

	m_fTime = 0.f;
	m_iMode = 0;
}

CDemonHunter_ElementalArrow_FlashEffect::~CDemonHunter_ElementalArrow_FlashEffect(void)
{
	Release();
}

void CDemonHunter_ElementalArrow_FlashEffect::Initialize()
{
	CEffect::Initialize();

	m_pTransformCom->m_vSize = D3DXVECTOR3(50.f, 50.f, 1.f);
	m_pTransformCom->m_vAngle.x = D3DXToRadian(90.f);
	m_pTransformCom->m_vPos = D3DXVECTOR3(0.f, 0.f, 30.f); // ?? 위치 잡아주자..
}

int CDemonHunter_ElementalArrow_FlashEffect::Update()
{
	CEffect::Update();

	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();
	
	switch(m_iMode)
	{
	case 0:
		Mode1();
		break;

	case 1:
		Mode2();
		break;
	}

	m_pTransformCom->m_mWorld = m_pTransformCom->m_mWorld * (*m_pWorld);

	return 0;
}

void CDemonHunter_ElementalArrow_FlashEffect::Render()
{
	CEffect::Render();
}

void CDemonHunter_ElementalArrow_FlashEffect::Release()
{

}

void CDemonHunter_ElementalArrow_FlashEffect::Mode1()
{
	if(m_fTime >= 0.1f)
	{
		m_fTime = 0.f;
		++m_iMode;
	}

	m_pTransformCom->m_vSize += D3DXVECTOR3(1.f, 1.f, 0.f) * 1000.f * CTimeMgr::GetInstance()->GetDeltaTime();
}

void CDemonHunter_ElementalArrow_FlashEffect::Mode2()
{
	if(m_fTime >= 0.1f)
	{
		m_fTime = 0.f;
		--m_iMode;
	}

	m_pTransformCom->m_vSize -= D3DXVECTOR3(1.f, 1.f, 0.f) * 1000.f * CTimeMgr::GetInstance()->GetDeltaTime();
}