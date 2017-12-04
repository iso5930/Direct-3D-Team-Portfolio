#include "StdAfx.h"
#include "Wizard_MagicMissile_CreateEffect.h"

CWizard_MagicMissile_CreateEffect::CWizard_MagicMissile_CreateEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXVECTOR3 _vDir, float _fCreateTime)
:CEffect(_tszObjKey, _eObjType, _pOwner)
{
	m_fCreateTime = _fCreateTime;
	m_fTime = 0.f;
	m_vDir = _vDir;

	// UpdateCom
	CUpdateCom* pUpdateCom = new CUpdateCom(UPDATE_TYPE_EFFECT);
	AddComponent(pUpdateCom);
}

CWizard_MagicMissile_CreateEffect::~CWizard_MagicMissile_CreateEffect(void)
{
	Release();
}

void CWizard_MagicMissile_CreateEffect::Initialize()
{
	CEffect::Initialize();
}

int CWizard_MagicMissile_CreateEffect::Update()
{
	CEffect::Update();

	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fTime >= m_fCreateTime)
	{
		Destroy();

		CWizard_MagicMissile_MissileEffect* pMissileEffect = new CWizard_MagicMissile_MissileEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner, m_vDir);
		m_pLayer->AddObject(pMissileEffect, LAYER_TYPE_EFFECT);

		CTransformCom* pTransformCom = (CTransformCom*)pMissileEffect->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = m_pTransformCom->m_vPos;
		pTransformCom->m_vAngle = m_pTransformCom->m_vAngle;
		pMissileEffect->Initialize();	
	}

	return 0;
}

void CWizard_MagicMissile_CreateEffect::Render()
{
	CEffect::Render();
}

void CWizard_MagicMissile_CreateEffect::Release()
{

}
