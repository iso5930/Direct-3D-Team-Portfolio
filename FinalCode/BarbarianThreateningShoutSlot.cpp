#include "StdAfx.h"
#include "BarbarianThreateningShoutSlot.h"

CBarbarianThreateningShoutSlot::CBarbarianThreateningShoutSlot()
{
	// SlotType
	m_eSlotType = SLOT_TYPE_BARBARIAN_TACTICS;

	// SlotID
	m_eSlotID = SLOT_ID_BARBARIAN_THREATENING_SHOUT;

	// CooldownTime
	m_fCooldownTime = 10.0f;

	// Time
	m_fTime = m_fCooldownTime;

	// Range
	m_fRange = 9999.f;

}

CBarbarianThreateningShoutSlot::~CBarbarianThreateningShoutSlot()
{
}

SLOT_RESULT CBarbarianThreateningShoutSlot::Begin(int _iMode)
{
	// Check Enable
	if (!m_bEnable)
	{
		CUIMgr::GetInstance()->CreateTextMessage(_T("아직은 사용 할 수 없습니다."));
		return SLOT_RESULT_COOLDOWN_TIEM;
	}

	// Check Rage
	if(m_pOwner->GetStat()->iRage < 15 * (1.0f - m_pOwner->GetReducedRageConsumption()))
	{
		CUIMgr::GetInstance()->CreateTextMessage(_T("분노가 부족 합니다."));
		return SLOT_RESULT_RAGE_EMPTY;
	}

	// Begin
	CSlot::Begin(_iMode);

	// Rage
	m_pOwner->GetStat()->iRage -= int(15 * (1.0f - m_pOwner->GetReducedRageConsumption()));

	// AddBuff
	m_pOwner->AddBuff(new Buff(BUFF_TYPE_SPRINT , 3.f));

	return SLOT_RESULT_NULL;
}

SLOT_RESULT CBarbarianThreateningShoutSlot::Action()
{
	return SLOT_RESULT_NULL;
}

SLOT_RESULT CBarbarianThreateningShoutSlot::End()
{
	return SLOT_RESULT_NULL;
}
