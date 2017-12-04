#include "StdAfx.h"
#include "WitchDoctorSoulHarvestSlot.h"

CWitchDoctorSoulHarvestSlot::CWitchDoctorSoulHarvestSlot()
{
	// SlotType
	m_eSlotType = SLOT_TYPE_WITCHDOCTOR_TERROR;

	// SlotID
	m_eSlotID = SLOT_ID_WITCHDOCTOR_SOUL_HARVEST;

	// CooldownTime
	m_fCooldownTime = 12.0f;

	// Time
	m_fTime = m_fCooldownTime;

	// Range
	m_fRange = 9999.f;

}

CWitchDoctorSoulHarvestSlot::~CWitchDoctorSoulHarvestSlot()
{
}

SLOT_RESULT CWitchDoctorSoulHarvestSlot::Begin(int _iMode)
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

SLOT_RESULT CWitchDoctorSoulHarvestSlot::Action()
{
	return SLOT_RESULT_NULL;
}

SLOT_RESULT CWitchDoctorSoulHarvestSlot::End()
{
	return SLOT_RESULT_NULL;
}
