#include "StdAfx.h"
#include "WizardFrostNovaSlot.h"

CWizardFrostNovaSlot::CWizardFrostNovaSlot()
{
	// SlotType
	m_eSlotType = SLOT_TYPE_WIZARD_DEFENSIVE;

	// SlotID
	m_eSlotID = SLOT_ID_WIZARD_FROST_NOVA;

	// ColldownTime
	m_fCooldownTime = 11.0f;

	// Time
	m_fTime = m_fCooldownTime;

	// Range
	m_fRange = 9999.f;

}

CWizardFrostNovaSlot::~CWizardFrostNovaSlot()
{
}

SLOT_RESULT CWizardFrostNovaSlot::Begin(int _iMode)
{
	// Check Enable
	if (!m_bEnable)
	{
		CUIMgr::GetInstance()->CreateTextMessage(_T("아직은 사용 할 수 없습니다."));
		return SLOT_RESULT_COOLDOWN_TIEM;
	}

	// Begin
	CSlot::Begin(_iMode);

	CSoundMgr::GetInstance()->PlaySoundForPlayer(_T("FROST_NOVA.ogg"));

	// 이펙트 생성
	CWizard_FrostNova_FrostEffect* pNovaEffect = new CWizard_FrostNova_FrostEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
	m_pOwner->GetLayer()->AddObject(pNovaEffect, LAYER_TYPE_EFFECT);

	CTransformCom* pTransformCom = (CTransformCom*)pNovaEffect->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = m_pTransformCom->m_vPos + D3DXVECTOR3(0.f, 70.f, 0.f);
	pNovaEffect->Initialize();

	pNovaEffect = new CWizard_FrostNova_FrostEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
	m_pOwner->GetLayer()->AddObject(pNovaEffect, LAYER_TYPE_EFFECT);

	pTransformCom = (CTransformCom*)pNovaEffect->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = m_pTransformCom->m_vPos + D3DXVECTOR3(0.f, 70.f, 0.f);
	pTransformCom->m_vAngle.y = D3DXToRadian(180.f);
	pNovaEffect->Initialize();
	
	int iRand = (rand() % 5) + 10;

	for(int i = 0; i < iRand; ++i)
	{
		int iRandAngle = rand() % 360;
		
		D3DXVECTOR3 vDir(0.f, 0.f, 1.f);
		D3DXMATRIX matRot;
		D3DXMatrixRotationY(&matRot, D3DXToRadian(float(iRandAngle)));
		D3DXVec3TransformNormal(&vDir, &vDir, &matRot);
		
		float fDelayTime = float(rand() % 11) * 0.01f;
		CWizard_FrostNova_ArrowEffect* pArrowEffect = new CWizard_FrostNova_ArrowEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner, &(vDir * 500.f), fDelayTime);
		m_pOwner->GetLayer()->AddObject(pArrowEffect, LAYER_TYPE_EFFECT);

		CTransformCom* pTransformCom = (CTransformCom*)pArrowEffect->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = m_pTransformCom->m_vPos + D3DXVECTOR3(0.f, 70.f, 0.f);
		pTransformCom->m_vAngle.y = D3DXToRadian((float)iRandAngle);
		pArrowEffect->Initialize();
	}

	return SLOT_RESULT_NULL;
}

SLOT_RESULT CWizardFrostNovaSlot::Action()
{
	return SLOT_RESULT_NULL;
}

SLOT_RESULT CWizardFrostNovaSlot::End()
{
	return SLOT_RESULT_NULL;
}
