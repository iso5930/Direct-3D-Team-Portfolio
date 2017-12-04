#include "StdAfx.h"
#include "BarbarianIgnorePainSlot.h"

CBarbarianIgnorePainSlot::CBarbarianIgnorePainSlot()
{
	// SlotType
	m_eSlotType = SLOT_TYPE_BARBARIAN_DEFENSIVE;

	// SlotID
	m_eSlotID = SLOT_ID_BARBARIAN_IGNORE_PAIN;

	// CooldownTime
	m_fCooldownTime = 30.0f;

	// Time
	m_fTime = m_fCooldownTime;

	// Range
	m_fRange = 9999.f;

}

CBarbarianIgnorePainSlot::~CBarbarianIgnorePainSlot()
{
}

SLOT_RESULT CBarbarianIgnorePainSlot::Begin(int _iMode)
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

SLOT_RESULT CBarbarianIgnorePainSlot::Action()
{
	return SLOT_RESULT_NULL;
}

SLOT_RESULT CBarbarianIgnorePainSlot::End()
{
	return SLOT_RESULT_NULL;
}
