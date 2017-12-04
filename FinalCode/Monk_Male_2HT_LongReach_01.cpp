#include "StdAfx.h"
#include "Monk_Male_2HT_LongReach_01.h"

CMonk_Male_2HT_LongReach_01::CMonk_Male_2HT_LongReach_01(void)
{
	m_eStateType = STATE_TYPE_MONK_MALE_2HT_LONGREACH_01;

	m_iMode = 0 ;

	m_iSlotNum = -1;
}

CMonk_Male_2HT_LongReach_01::~CMonk_Male_2HT_LongReach_01(void)
{
}

void CMonk_Male_2HT_LongReach_01::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(62);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CMonk_Male_2HT_LongReach_01::Action()
{
	switch(m_iMode)
	{
	case 0: //ó������ ������ �ִ»���
		return Mode0();

	case 1: //�ѹ��̻� ������ ����
		return Mode1();

	case 2: //�ٽ� �������� 
		return Mode2();
	}

	return NULL;
}


CPlayerState* CMonk_Male_2HT_LongReach_01::Mode0()
{
	m_iSlotNum = CPlayerState::UsingKeyMouse();

	if(m_iSlotNum == -1)
	{
		m_iMode = 1;	
	}
	else if(m_pAnimController->m_dFrameTime - 0.2 <= m_pAnimController->GetTrackPos())
	{		
		if (m_pOwner->GetSlot(m_iSlotNum)->GetSlotID() == SLOT_ID_MONK_DEADLY_REACH && 	m_pOwner->GetSlot(m_iSlotNum)->Begin(0) == SLOT_RESULT_NULL)
		{
			return new CMonk_Male_2HT_LongReach_02;
		}
		else
		{
			return new CMonk_Male_2HT_Idle;
		}
	}	

	return NULL;
}

CPlayerState* CMonk_Male_2HT_LongReach_01::Mode1()
{
	if(m_pAnimController->m_dFrameTime - 0.2 <= m_pAnimController->GetTrackPos())
	{
		return new CMonk_Male_2HT_Idle;	
	}

	m_iSlotNum = CPlayerState::UsingKeyMouse();

	if ( m_iSlotNum == -1)
		return NULL;
	else if (m_pOwner->GetSlot(m_iSlotNum)->GetSlotID() == SLOT_ID_MONK_DEADLY_REACH)
		m_iMode = 2;

	return NULL;
}

CPlayerState* CMonk_Male_2HT_LongReach_01::Mode2()
{
	if(m_pAnimController->m_dFrameTime - 0.2 <= m_pAnimController->GetTrackPos())
	{
		if (m_pOwner->GetSlot(m_iSlotNum)->GetSlotID() == SLOT_ID_MONK_DEADLY_REACH && 	m_pOwner->GetSlot(m_iSlotNum)->Begin(0) == SLOT_RESULT_NULL)
		{
			return new CMonk_Male_2HT_LongReach_02;
		}
		else
		{
			return new CMonk_Male_2HT_Idle;
		}
	}

	return NULL;
}