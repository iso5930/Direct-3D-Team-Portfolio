#include "StdAfx.h"
#include "Wizard_WaveOfForce_CreateEffect.h"

CWizard_WaveOfForce_CreateEffect::CWizard_WaveOfForce_CreateEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	m_fTime = 0.f;
	m_iMode = 0;
	m_fCreateTime = 0.f;
	m_iCreateCount = 0;
}

CWizard_WaveOfForce_CreateEffect::~CWizard_WaveOfForce_CreateEffect(void)
{
	Release();
}

void CWizard_WaveOfForce_CreateEffect::Initialize()
{
	CEffect::Initialize();
}

int CWizard_WaveOfForce_CreateEffect::Update()
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

void CWizard_WaveOfForce_CreateEffect::Render()
{	
	CEffect::Render();
}

void CWizard_WaveOfForce_CreateEffect::Release()
{

}

void CWizard_WaveOfForce_CreateEffect::Mode1()
{
	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fTime >= 0.5f)
	{
		m_fTime = 0.f;
		++m_iMode;
	}
}

void CWizard_WaveOfForce_CreateEffect::Mode2()
{
	m_fCreateTime += CTimeMgr::GetInstance()->GetDeltaTime();
	m_fTime +=	CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fCreateTime >= 0.05f)
	{
		m_fCreateTime = 0.f;

		CWizard_WaveOfForce_WaveEffect* pWaveEffect = new CWizard_WaveOfForce_WaveEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
		m_pLayer->AddObject(pWaveEffect, LAYER_TYPE_EFFECT);

		CTransformCom* pTransformCom = (CTransformCom*)pWaveEffect->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = m_pTransformCom->m_vPos;
		pWaveEffect->Initialize();

		if(m_iCreateCount == 0)
		{
			pWaveEffect->AddCCollision();
		}

		++m_iCreateCount;
	}

	if(m_fTime >= 0.2f)
	{
		Destroy();
	}
}