#include "StdAfx.h"
#include "WizardArchonSlot.h"

CWizardArchonSlot::CWizardArchonSlot()
{
	// SlotType
	m_eSlotType = SLOT_TYPE_WIZARD_MASTERY;

	// SlotID
	m_eSlotID = SLOT_ID_WIZARD_ARCHON;

	// CooldownTime
	m_fCooldownTime = 0.0f;

	// Time
	m_fTime = m_fCooldownTime;

	// Range
	m_fRange = 9999.f;

}

CWizardArchonSlot::~CWizardArchonSlot()
{
}

SLOT_RESULT CWizardArchonSlot::Begin(int _iMode)
{
	// Check Enable
	if (!m_bEnable)
	{
		CUIMgr::GetInstance()->CreateTextMessage(_T("아직은 사용 할 수 없습니다."));
		return SLOT_RESULT_COOLDOWN_TIEM;
	}

	// Begin
	CSlot::Begin(_iMode);

	return SLOT_RESULT_NULL;
}

SLOT_RESULT CWizardArchonSlot::Action()
{
	return SLOT_RESULT_NULL;
}

SLOT_RESULT CWizardArchonSlot::End()
{
	return SLOT_RESULT_NULL;
}
