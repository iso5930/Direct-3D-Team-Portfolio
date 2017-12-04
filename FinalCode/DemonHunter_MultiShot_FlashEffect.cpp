#include "StdAfx.h"
#include "DemonHunter_MultiShot_FlashEffect.h"

CDemonHunter_MultiShot_FlashEffect::CDemonHunter_MultiShot_FlashEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner)
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
	CMaterialCom* pMaterialCom = new CMaterialCom(NULL, _T("Effect_MultiShot_Flash"));
	AddComponent(pMaterialCom);

	m_fTime = 0.f;
	m_iMode = 0;
}

CDemonHunter_MultiShot_FlashEffect::~CDemonHunter_MultiShot_FlashEffect(void)
{
	Release();
}

void CDemonHunter_MultiShot_FlashEffect::Initialize()
{
	CEffect::Initialize();

	m_pTransformCom->m_vSize = D3DXVECTOR3(200.f, 200.f, 1.f);
	m_pTransformCom->m_vAngle.x = D3DXToRadian(90.f);
}

int CDemonHunter_MultiShot_FlashEffect::Update()
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

	return 0;
}

void CDemonHunter_MultiShot_FlashEffect::Render()
{
	CEffect::Render();
}

void CDemonHunter_MultiShot_FlashEffect::Release()
{

}

void CDemonHunter_MultiShot_FlashEffect::Mode1()
{
	if(m_fTime >= 0.1f)
	{
		m_fTime = 0.f;
		++m_iMode;
	}

	m_pTransformCom->m_vSize += D3DXVECTOR3(1.f, 1.f, 0.f) * 1000.f * CTimeMgr::GetInstance()->GetDeltaTime();
}	

void CDemonHunter_MultiShot_FlashEffect::Mode2()
{
	m_pTransformCom->m_vSize -= D3DXVECTOR3(1.f, 1.f, 0.f) * 1000.f * CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fTime >= 0.2f)
	{
		Destroy();
	}
}