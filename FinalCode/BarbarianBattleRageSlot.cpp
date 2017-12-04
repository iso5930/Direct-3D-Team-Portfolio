#include "StdAfx.h"
#include "BarbarianBattleRageSlot.h"

CBarbarianBattleRageSlot::CBarbarianBattleRageSlot()
{
	// SlotType
	m_eSlotType = SLOT_TYPE_BARBARIAN_TACTICS;

	// SlotID
	m_eSlotID = SLOT_ID_BARBARIAN_BATTLE_RAGE;

	// CooldownTime
	m_fCooldownTime = 0.0f;

	// Time
	m_fTime = m_fCooldownTime;

	// Range
	m_fRange = 9999.f;
}

CBarbarianBattleRageSlot::~CBarbarianBattleRageSlot()
{
}

SLOT_RESULT CBarbarianBattleRageSlot::Begin(int _iMode)
{
	// Check Enable
	if (!m_bEnable)
	{
		CUIMgr::GetInstance()->CreateTextMessage(_T("아직은 사용 할 수 없습니다."));
		return SLOT_RESULT_COOLDOWN_TIEM;
	}

	// Check Rage
	if(m_pOwner->GetStat()->iRage < 25 * (1.0f - m_pOwner->GetReducedRageConsumption()))
	{
		CUIMgr::GetInstance()->CreateTextMessage(_T("분노가 부족 합니다."));
		return SLOT_RESULT_RAGE_EMPTY;
	}

	// Begin
	CSlot::Begin(_iMode);

	// Rage
	m_pOwner->GetStat()->iRage -= int(25 * (1.0f - m_pOwner->GetReducedRageConsumption()));

	// AddBuff
	m_pOwner->AddBuff(new Buff(BUFF_TYPE_BATTLE_RAGE , 5.f));

	return SLOT_RESULT_NULL;
}

SLOT_RESULT CBarbarianBattleRageSlot::Action()
{
	return SLOT_RESULT_NULL;
}

SLOT_RESULT CBarbarianBattleRageSlot::End()
{
	return SLOT_RESULT_NULL;
}
