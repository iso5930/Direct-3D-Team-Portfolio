#include "StdAfx.h"
#include "Wizard_ExplosiveBlast_DummyEffect.h"

CWizard_ExplosiveBlast_DummyEffect::CWizard_ExplosiveBlast_DummyEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	m_fTime = 0.f;
	m_iMode = 0;
	m_fCreateTime = 0.f;

	m_pCastingEffect = NULL;
}

CWizard_ExplosiveBlast_DummyEffect::~CWizard_ExplosiveBlast_DummyEffect(void)
{
	Release();
}

void CWizard_ExplosiveBlast_DummyEffect::Initialize()
{
	CEffect::Initialize();

	m_pCastingEffect = new CWizard_ExplosiveBlast_CastingEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
	m_pLayer->AddObject(m_pCastingEffect, LAYER_TYPE_EFFECT);
	m_pCastingEffect->Initialize();
}

int CWizard_ExplosiveBlast_DummyEffect::Update()
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

void CWizard_ExplosiveBlast_DummyEffect::Render()
{	
	CEffect::Render();
}

void CWizard_ExplosiveBlast_DummyEffect::Release()
{
	if(m_pCastingEffect != NULL)
	{
		m_pCastingEffect->Destroy();
		m_pCastingEffect = NULL;
	}
}

void CWizard_ExplosiveBlast_DummyEffect::Mode1()
{
	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fTime >= 1.5f)
	{
		m_fTime = 0.f;
		++m_iMode;
	}
}

void CWizard_ExplosiveBlast_DummyEffect::Mode2()
{
	CSoundMgr::GetInstance()->PlaySoundForPlayer(_T("EXPLOSIVE_BLAST_EFFECT.ogg"));

	CTransformCom* pOwnerTransformCom = (CTransformCom*)m_pOwner->GetComponent(COM_TYPE_TRANSFORM);
	CWizard_ExplosiveBlase_FlashEffect* pFlashEffect = new CWizard_ExplosiveBlase_FlashEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
	m_pLayer->AddObject(pFlashEffect, LAYER_TYPE_EFFECT);

	CTransformCom* pTransformCom = (CTransformCom*)pFlashEffect->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = pOwnerTransformCom->m_vPos;
	pFlashEffect->Initialize();

	Destroy();
}