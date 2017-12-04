#include "StdAfx.h"
#include "DemonHunterCompanionSlot.h"

CDemonHunterCompanionSlot::CDemonHunterCompanionSlot()
{
	// SlotType
	m_eSlotType = SLOT_TYPE_DEMONHUNTER_HUNTING;

	// SlotID
	m_eSlotID = SLOT_ID_DEMONHUNTER_COMPANION;

	// CooldownTime
	m_fCooldownTime = 30.0f;

	// Time
	m_fTime = m_fCooldownTime;

	// Range
	m_fRange = 9999.f;

}

CDemonHunterCompanionSlot::~CDemonHunterCompanionSlot()
{
}

SLOT_RESULT CDemonHunterCompanionSlot::Begin(int _iMode)
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

SLOT_RESULT CDemonHunterCompanionSlot::Action()
{
	return SLOT_RESULT_NULL;
}

SLOT_RESULT CDemonHunterCompanionSlot::End()
{
	return SLOT_RESULT_NULL;
}
