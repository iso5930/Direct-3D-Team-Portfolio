#include "StdAfx.h"
#include "DemonHunter_Preparation_DecalEffect.h"

CDemonHunter_Preparation_DecalEffect::CDemonHunter_Preparation_DecalEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner)
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
	CMaterialCom* pMaterialCom = new CMaterialCom(NULL, _T("Effect_Preparation_Decal"));
	AddComponent(pMaterialCom);

	m_fTime = 0.f;
	m_iMode = 0;
	m_fAlpha = 0.f;
}

CDemonHunter_Preparation_DecalEffect::~CDemonHunter_Preparation_DecalEffect(void)
{
	Release();
}

void CDemonHunter_Preparation_DecalEffect::Initialize()
{
	CEffect::Initialize();

	m_pTransformCom->m_vSize = D3DXVECTOR3(300.f, 300.f, 300.f);

	CDemonHunter_Preparation_BuffEffect* pBuffEffect = new CDemonHunter_Preparation_BuffEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
	m_pLayer->AddObject(pBuffEffect, LAYER_TYPE_EFFECT);

	CTransformCom* pTransformCom = (CTransformCom*)pBuffEffect->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = m_pTransformCom->m_vPos + D3DXVECTOR3(0.f, 60.f, 0.f);
	pBuffEffect->Initialize();
}

int CDemonHunter_Preparation_DecalEffect::Update()
{
	CEffect::Update();

	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();
	m_fAlpha += 6.f * CTimeMgr::GetInstance()->GetDeltaTime();

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

void CDemonHunter_Preparation_DecalEffect::Render()
{
	CEffect::Render();
}

void CDemonHunter_Preparation_DecalEffect::Release()
{

}

void CDemonHunter_Preparation_DecalEffect::Mode1()
{
	if(m_fTime >= 0.1f)
	{
		m_fTime = 0.f;
		++m_iMode;
	}

	m_pTransformCom->m_vSize += D3DXVECTOR3(1.f, 1.f, 1.f) * 1000.f * CTimeMgr::GetInstance()->GetDeltaTime();	
}

void CDemonHunter_Preparation_DecalEffect::Mode2()
{
	if(m_fTime >= 0.5f)
	{
		Destroy();
	}

	m_pTransformCom->m_vSize -= D3DXVECTOR3(1.f, 1.f, 1.f) * 500.f * CTimeMgr::GetInstance()->GetDeltaTime();
}