#include "StdAfx.h"
#include "MonkMysticAllySlot.h"

CMonkMysticAllySlot::CMonkMysticAllySlot()
{
	// SlotType
	m_eSlotType = SLOT_TYPE_MONK_FOCUS;

	// SlotID
	m_eSlotID = SLOT_ID_MONK_MYSTIC_ALLY;

	// CooldownTime
	m_fCooldownTime = 30.0f;

	// Time
	m_fTime = m_fCooldownTime;

	// Range
	m_fRange = 9999.f;

}

CMonkMysticAllySlot::~CMonkMysticAllySlot()
{
}

SLOT_RESULT CMonkMysticAllySlot::Begin(int _iMode)
{
	// Check Enable
	if (!m_bEnable)
	{
		CUIMgr::GetInstance()->CreateTextMessage(_T("아직은 사용 할 수 없습니다."));
		return SLOT_RESULT_COOLDOWN_TIEM;
	}

	// Mode
	CSlot::Begin(_iMode);

	return SLOT_RESULT_NULL;
}

SLOT_RESULT CMonkMysticAllySlot::Action()
{
	return SLOT_RESULT_NULL;
}

SLOT_RESULT CMonkMysticAllySlot::End()
{
	return SLOT_RESULT_NULL;
}
