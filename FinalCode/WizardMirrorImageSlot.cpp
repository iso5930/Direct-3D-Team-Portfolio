#include "StdAfx.h"
#include "WizardMirrorImageSlot.h"

CWizardMirrorImageSlot::CWizardMirrorImageSlot()
{
	// SlotType
	m_eSlotType = SLOT_TYPE_WIZARD_MASTERY;

	// SlotID
	m_eSlotID = SLOT_ID_WIZARD_MIRROR_IMAGE;
	
	// ColldownTime
	m_fCooldownTime = 15.0f;

	// Time
	m_fTime = m_fCooldownTime;

	// Range
	m_fRange = 9999.f;

}

CWizardMirrorImageSlot::~CWizardMirrorImageSlot()
{
}

SLOT_RESULT CWizardMirrorImageSlot::Begin(int _iMode)
{
	// Check Enable
	if (!m_bEnable)
	{
		CUIMgr::GetInstance()->CreateTextMessage(_T("아직은 사용 할 수 없습니다."));
		return SLOT_RESULT_COOLDOWN_TIEM;
	}

	// Begin
	CSlot::Begin(_iMode);

	for(int i = 0; i < 2; ++i)
	{
		CWizard_MirrorImage_MirrorImageEffect* pMirrorEffect = new CWizard_MirrorImage_MirrorImageEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
		m_pOwner->GetLayer()->AddObject(pMirrorEffect, LAYER_TYPE_EFFECT);

		CTransformCom* pTransformCom = (CTransformCom*)pMirrorEffect->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = m_pTransformCom->m_vPos;
		pTransformCom->m_vAngle = m_pTransformCom->m_vAngle;
		pMirrorEffect->Initialize();
	}

	return SLOT_RESULT_NULL;
}

SLOT_RESULT CWizardMirrorImageSlot::Action()
{
	return SLOT_RESULT_NULL;
}

SLOT_RESULT CWizardMirrorImageSlot::End()
{
	return SLOT_RESULT_NULL;
}
