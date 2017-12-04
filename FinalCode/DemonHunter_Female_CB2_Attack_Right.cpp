#include "StdAfx.h"
#include "DemonHunter_Female_CB2_Attack_Right.h"

CDemonHunter_Female_CB2_Attack_Right::CDemonHunter_Female_CB2_Attack_Right()
{
	// StateType
	m_eStateType = STATE_TYPE_DEMONHUNTER_FEMALE_CB2_ATTACK_RIGHT;

}

CDemonHunter_Female_CB2_Attack_Right::~CDemonHunter_Female_CB2_Attack_Right()
{
}

void CDemonHunter_Female_CB2_Attack_Right::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(14);
}

CPlayerState* CDemonHunter_Female_CB2_Attack_Right::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		// Find Priority Key and SlotNo
		int iSlotNum = CPlayerState::UsingKeyMouse();

		// If None Input..
		if(iSlotNum == -1 )
		{
			return new CDemonHunter_Female_CB2_Idle;
		}

		// Slot
		SLOT_ID eSlotID = m_pOwner->GetSlot(iSlotNum)->GetSlotID();
		if(eSlotID == SLOT_ID_DEMONHUNTER_FAR_ATTACK)
		{
			if(m_pOwner->GetSlot(iSlotNum)->Begin(1) == SLOT_RESULT_NULL)
			{
				return new CDemonHunter_Female_CB2_Attack_Left;
			}
		}
		// EntanglingShot
		else if(eSlotID == SLOT_ID_DEMONHUNTER_ENTANGLING_SHOT)
		{
			if(m_pOwner->GetSlot(iSlotNum)->Begin(1) == SLOT_RESULT_NULL)
			{
				return new CDemonHunter_Female_CB2_Attack_Left;
			}
		}
		// HungeringArrow
		else if(eSlotID == SLOT_ID_DEMONHUNTER_HUNGERING_ARROW)
		{
			if(m_pOwner->GetSlot(iSlotNum)->Begin(1) == SLOT_RESULT_NULL)
			{
				return new CDemonHunter_Female_CB2_Attack_Left;
			}
		}

		// EvasiveFire
		else if(eSlotID == SLOT_ID_DEMONHUNTER_EVASIVE_FIRE)
		{
			if(m_pOwner->GetSlot(iSlotNum)->Begin(1) == SLOT_RESULT_NULL)
			{
				return new CDemonHunter_Female_CB2_Attack_Left;
			}
		}

		return new CDemonHunter_Female_CB2_Idle;
	}

	return NULL;
}