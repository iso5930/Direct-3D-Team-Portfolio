#include "StdAfx.h"
#include "BarbarianWarCrySlot.h"

CBarbarianWarCrySlot::CBarbarianWarCrySlot()
{
	// SlotType
	m_eSlotType = SLOT_TYPE_BARBARIAN_TACTICS;

	// SlotID
	m_eSlotID = SLOT_ID_BARBARIAN_WAR_CRY;

	// CooldownTime
	m_fCooldownTime = 20.0f;

	// Time
	m_fTime = m_fCooldownTime;

	// Range
	m_fRange = 9999.f;

}

CBarbarianWarCrySlot::~CBarbarianWarCrySlot()
{
}

SLOT_RESULT CBarbarianWarCrySlot::Begin(int _iMode)
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

	// Check Rage
	if(m_pOwner->GetStat()->iRage < 20 * (1.0f - m_pOwner->GetReducedRageConsumption()))
	{
		CUIMgr::GetInstance()->CreateTextMessage(_T("분노가 부족 합니다."));
		return SLOT_RESULT_RAGE_EMPTY;
	}

	// Begin
	CSlot::Begin(_iMode);

	// Rage
	m_pOwner->GetStat()->iRage -= int(20 * (1.0f - m_pOwner->GetReducedRageConsumption()));

	// AddBuff
	m_pOwner->AddBuff(new Buff(BUFF_TYPE_SPRINT , 120.f));

	return SLOT_RESULT_NULL;
}

SLOT_RESULT CBarbarianWarCrySlot::Action()
{
	return SLOT_RESULT_NULL;
}

SLOT_RESULT CBarbarianWarCrySlot::End()
{
	return SLOT_RESULT_NULL;
}
