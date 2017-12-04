#include "StdAfx.h"
#include "Wizard_MagicAttack_CreateEffect.h"

CWizard_MagicAttack_CreateEffect::CWizard_MagicAttack_CreateEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXVECTOR3* _pDir, float _fTime)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);

	m_vDir = (*_pDir);

	m_fTime = 0.f;
	m_fCreateTime = _fTime;
}	

CWizard_MagicAttack_CreateEffect::~CWizard_MagicAttack_CreateEffect(void)
{
	Release();
}

void CWizard_MagicAttack_CreateEffect::Initialize()
{
	CEffect::Initialize();
}

int CWizard_MagicAttack_CreateEffect::Update()
{
	CEffect::Update();

	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fTime >= m_fCreateTime)
	{
		Destroy();

		CWizard_MagicAttack_MissileEffect* pMissileEffect = new CWizard_MagicAttack_MissileEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner, &m_vDir);
		m_pLayer->AddObject(pMissileEffect, LAYER_TYPE_EFFECT);

		CTransformCom* pTrnasformCom = (CTransformCom*)pMissileEffect->GetComponent(COM_TYPE_TRANSFORM);
		pTrnasformCom->m_vPos = m_pTransformCom->m_vPos;
		pMissileEffect->Initialize();
	}

	return 0;
}

void CWizard_MagicAttack_CreateEffect::Render()
{
	CEffect::Render();
}

void CWizard_MagicAttack_CreateEffect::Release()
{

}
