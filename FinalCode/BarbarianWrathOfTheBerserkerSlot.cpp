#include "StdAfx.h"
#include "BarbarianWrathOfTheBerserkerSlot.h"

CBarbarianWrathOfTheBerserkerSlot::CBarbarianWrathOfTheBerserkerSlot()
{
	// SlotType
	m_eSlotType = SLOT_TYPE_BARBARIAN_RAGE;

	// SlotID
	m_eSlotID = SLOT_ID_BARBARIAN_WRATH_OF_THE_BERSERKER;

	// CooldownTime
	m_fCooldownTime = 120.0f;

	// Time
	m_fTime = m_fCooldownTime;

	// Range
	m_fRange = 9999.f;

}

CBarbarianWrathOfTheBerserkerSlot::~CBarbarianWrathOfTheBerserkerSlot()
{
}

SLOT_RESULT CBarbarianWrathOfTheBerserkerSlot::Begin(int _iMode)
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
	m_pOwner->AddBuff(new Buff(BUFF_TYPE_WRATH_OF_BERSERKER , 20.f));

	return SLOT_RESULT_NULL;
}

SLOT_RESULT CBarbarianWrathOfTheBerserkerSlot::Action()
{
	return SLOT_RESULT_NULL;
}

SLOT_RESULT CBarbarianWrathOfTheBerserkerSlot::End()
{
	return SLOT_RESULT_NULL;
}
