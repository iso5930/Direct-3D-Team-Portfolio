#include "StdAfx.h"
#include "Monk_Male_STF_DebilitatingBlows_01.h"

CMonk_Male_STF_DebilitatingBlows_01::CMonk_Male_STF_DebilitatingBlows_01(void)
{
	m_eStateType = STATE_TYPE_MONK_MALE_STF_DEBILITATINGBLOWS_01;

	m_iMode = 0 ;

	m_iSlotNum = -1;
}

CMonk_Male_STF_DebilitatingBlows_01::~CMonk_Male_STF_DebilitatingBlows_01(void)
{
}

void CMonk_Male_STF_DebilitatingBlows_01::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(70);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CMonk_Male_STF_DebilitatingBlows_01::Action()
{
	switch(m_iMode)
	{
	case 0: //처음부터 누르고 있는상태
		return Mode0();

	case 1: //한번이상 때어진 상태
		return Mode1();

	case 2: //다시 눌렷을때 
		return Mode2();
	}

	return NULL;
}

CPlayerState* CMonk_Male_STF_DebilitatingBlows_01::Mode0()
{
	m_iSlotNum = CPlayerState::UsingKeyMouse();
	
	if(m_iSlotNum == -1)
	{
		m_iMode = 1;	
	}
	else if(m_pAnimController->m_dFrameTime - 0.2 <= m_pAnimController->GetTrackPos())
	{		
		if (m_pOwner->GetSlot(m_iSlotNum)->GetSlotID() == SLOT_ID_MONK_CRIPPLING_WAVE && 	m_pOwner->GetSlot(m_iSlotNum)->Begin(0) == SLOT_RESULT_NULL)
		{
			return new CMonk_Male_STF_DebilitatingBlows_02;
		}
		else
		{
			return new CMonk_Male_STF_Idle;
		}
	}	

	return NULL;
}

CPlayerState* CMonk_Male_STF_DebilitatingBlows_01::Mode1()
{

	if(m_pAnimController->m_dFrameTime - 0.2 <= m_pAnimController->GetTrackPos())
	{
		return new CMonk_Male_STF_Idle;	
	}

	m_iSlotNum = CPlayerState::UsingKeyMouse();

	if ( m_iSlotNum == -1)
		return NULL;
	else if (m_pOwner->GetSlot(m_iSlotNum)->GetSlotID() == SLOT_ID_MONK_CRIPPLING_WAVE)
		m_iMode = 2;

	return NULL;
		
}

CPlayerState* CMonk_Male_STF_DebilitatingBlows_01::Mode2()
{
	if(m_pAnimController->m_dFrameTime - 0.2 <= m_pAnimController->GetTrackPos())
	{
		if (m_pOwner->GetSlot(m_iSlotNum)->GetSlotID() == SLOT_ID_MONK_CRIPPLING_WAVE && 	m_pOwner->GetSlot(m_iSlotNum)->Begin(0) == SLOT_RESULT_NULL)
		{
			return new CMonk_Male_STF_DebilitatingBlows_02;
		}
		else
		{
			return new CMonk_Male_STF_Idle;
		}
	}

	return NULL;
}