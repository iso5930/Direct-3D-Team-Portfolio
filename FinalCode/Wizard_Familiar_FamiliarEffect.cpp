#include "StdAfx.h"
#include "Wizard_Familiar_FamiliarEffect.h"

CWizard_Familiar_FamiliarEffect::CWizard_Familiar_FamiliarEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	m_fTime = 0.f;
	m_iMode = 0;

	m_fCreateTime = 0.f;

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
	CMaterialCom* pMaterialCom = new CMaterialCom(NULL, _T("Effect_StormArmor_Flash"));
	AddComponent(pMaterialCom);
	
	m_fDeathTime = 0.f;
}

CWizard_Familiar_FamiliarEffect::~CWizard_Familiar_FamiliarEffect(void)
{
	Release();
}

void CWizard_Familiar_FamiliarEffect::Initialize()
{
	CEffect::Initialize();

	m_pTransformCom->m_vSize = D3DXVECTOR3(20.f, 20.f, 1.f);
	m_pTransformCom->m_vAngle.y = D3DXToRadian(-45.f);
	m_pTransformCom->m_vPos = D3DXVECTOR3(30.f, 120.f, 30.f);
}

int CWizard_Familiar_FamiliarEffect::Update()
{
	CEffect::Update();

	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();
	m_fCreateTime += CTimeMgr::GetInstance()->GetDeltaTime();

	switch(m_iMode)
	{
	case 0:
		Mode1();
		break;

	case 1:
		Mode2();
		break;
	}

	CTransformCom* pTransformCom = (CTransformCom*)m_pOwner->GetComponent(COM_TYPE_TRANSFORM);
	m_pTransformCom->m_mWorld *= pTransformCom->m_mTrans;

	if(m_fCreateTime >= 0.1f)
	{
		m_fCreateTime = 0.f;

		D3DXVECTOR3 vPos = D3DXVECTOR3(0.f, 0.f, 0.f);
		D3DXVec3TransformCoord(&vPos, &vPos, &m_pTransformCom->m_mWorld);

		CWizard_Familiar_AfterImageEffect* pAfterEffect = new CWizard_Familiar_AfterImageEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
		m_pLayer->AddObject(pAfterEffect, LAYER_TYPE_EFFECT);

		CTransformCom* pTransformCom = (CTransformCom*)pAfterEffect->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = vPos - D3DXVECTOR3(1.f, 0.f, 1.f);
		pAfterEffect->Initialize();
	}

	m_fDeathTime += CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fDeathTime >= 9.f)
	{
		Destroy();
	}

	return 0;
}

void CWizard_Familiar_FamiliarEffect::Render()
{
	CEffect::Render();
}

void CWizard_Familiar_FamiliarEffect::Release()
{
	
}

void CWizard_Familiar_FamiliarEffect::Mode1()
{
	if(m_fTime >= 0.1f)
	{
		m_fTime = 0.f;
		++m_iMode;
	}

	m_pTransformCom->m_vSize += D3DXVECTOR3(1.f, 1.f, 0.f) * 1000.f * CTimeMgr::GetInstance()->GetDeltaTime();
}

void CWizard_Familiar_FamiliarEffect::Mode2()
{
	if(m_fTime >= 0.1f)
	{
		m_fTime = 0.f;
		--m_iMode;
	}

	m_pTransformCom->m_vSize -= D3DXVECTOR3(1.f, 1.f, 0.f) * 1000.f * CTimeMgr::GetInstance()->GetDeltaTime();
}	
