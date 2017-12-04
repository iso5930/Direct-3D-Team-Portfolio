#include "StdAfx.h"
#include "BarbarianCallOfTheAncientsSlot.h"

CBarbarianCallOfTheAncientsSlot::CBarbarianCallOfTheAncientsSlot()
{
	// SlotType
	m_eSlotType = SLOT_TYPE_BARBARIAN_RAGE;

	// SlotID
	m_eSlotID = SLOT_ID_BARBARIAN_CALL_OF_THE_ANCIENTS;

	// CooldownTime
	m_fCooldownTime = 120.0f;

	// Time
	m_fTime = m_fCooldownTime;

	// Range
	m_fRange = 9999.f;
}

CBarbarianCallOfTheAncientsSlot::~CBarbarianCallOfTheAncientsSlot()
{
}

SLOT_RESULT CBarbarianCallOfTheAncientsSlot::Begin(int _iMode)
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

SLOT_RESULT CBarbarianCallOfTheAncientsSlot::Action()
{
	return SLOT_RESULT_NULL;
}

SLOT_RESULT CBarbarianCallOfTheAncientsSlot::End()
{
	return SLOT_RESULT_NULL;
}
