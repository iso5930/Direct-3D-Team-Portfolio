#include "StdAfx.h"
#include "WitchDoctorSpiritWalkSlot.h"

CWitchDoctorSpiritWalkSlot::CWitchDoctorSpiritWalkSlot()
{
	// SlotType
	m_eSlotType = SLOT_TYPE_WITCHDOCTOR_DEFENSIVE;

	// SlotID
	m_eSlotID = SLOT_ID_WITCHDOCTOR_SPIRIT_WALK;

	// CooldownTime
	m_fCooldownTime = 10.0f;

	// Time
	m_fTime = m_fCooldownTime;

	// Range
	m_fRange = 9999.f;

}

CWitchDoctorSpiritWalkSlot::~CWitchDoctorSpiritWalkSlot()
{
}

SLOT_RESULT CWitchDoctorSpiritWalkSlot::Begin(int _iMode)
{
	// Check Enable
	if (!m_bEnable)
	{
		CUIMgr::GetInstance()->CreateTextMessage(_T("아직은 사용 할 수 없습니다."));
		return SLOT_RESULT_COOLDOWN_TIEM;
	}

	// Begin
	CSlot::Begin(_iMode);

	// AddBuff
	m_pOwner->AddBuff(new Buff(BUFF_TYPE_WITCHDOCTOR_SPIRITWALK , 1.f));

	return SLOT_RESULT_NULL;
}

SLOT_RESULT CWitchDoctorSpiritWalkSlot::Action()
{
	return SLOT_RESULT_NULL;
}

SLOT_RESULT CWitchDoctorSpiritWalkSlot::End()
{
	return SLOT_RESULT_NULL;
}
