#include "StdAfx.h"
#include "WitchDoctorFetishArmySlot.h"

CWitchDoctorFetishArmySlot::CWitchDoctorFetishArmySlot()
{
	// SlotType
	m_eSlotType = SLOT_TYPE_WITCHDOCTOR_VOODOO;

	// SlotID
	m_eSlotID = SLOT_ID_WITCHDOCTOR_FETISH_ARMY;

	// CooldownTime
	m_fCooldownTime = 120.0f;

	// Time
	m_fTime = m_fCooldownTime;

	// Range
	m_fRange = 9999.f;

}

CWitchDoctorFetishArmySlot::~CWitchDoctorFetishArmySlot()
{
}

SLOT_RESULT CWitchDoctorFetishArmySlot::Begin(int _iMode)
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

SLOT_RESULT CWitchDoctorFetishArmySlot::Action()
{
	return SLOT_RESULT_NULL;
}

SLOT_RESULT CWitchDoctorFetishArmySlot::End()
{
	return SLOT_RESULT_NULL;
}
