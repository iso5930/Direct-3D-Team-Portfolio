#include "StdAfx.h"
#include "BarbarianMagicAttackSlot.h"

CBarbarianMagicAttackSlot::CBarbarianMagicAttackSlot()
{
	// SlotType
	m_eSlotType = SLOT_TYPE_BARBARIAN_SECONDARY;

	// SlotID
	m_eSlotID = SLOT_ID_BARBARIAN_MAGIC_ATTACK;

	// CooldownTime
	m_fCooldownTime = 0.0f;

	// Time
	m_fTime = m_fCooldownTime;

	// Range
	m_fRange = 9999.f;

}

CBarbarianMagicAttackSlot::~CBarbarianMagicAttackSlot()
{
}

SLOT_RESULT CBarbarianMagicAttackSlot::Begin(int _iMode)
{
	// Check Enable
	if (!m_bEnable)
	{
		CUIMgr::GetInstance()->CreateTextMessage(_T("아직은 사용 할 수 없습니다."));
		return SLOT_RESULT_COOLDOWN_TIEM;
	}

	// Check Pick
	if (CInputMgr::GetInstance()->GetPickPos() == NULL)
	{
		CUIMgr::GetInstance()->CreateTextMessage(_T("유효하지 않은 지역입니다."));
		return SLOT_RESULT_ERROR_PICK;
	}

	// Begin
	CSlot::Begin(_iMode);

	return SLOT_RESULT_NULL;
}

SLOT_RESULT CBarbarianMagicAttackSlot::Action()
{
	return SLOT_RESULT_NULL;
}

SLOT_RESULT CBarbarianMagicAttackSlot::End()
{
	return SLOT_RESULT_NULL;
}
