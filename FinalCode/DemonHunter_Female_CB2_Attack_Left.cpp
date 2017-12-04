#include "StdAfx.h"
#include "DemonHunter_Female_CB2_Attack_Left.h"

CDemonHunter_Female_CB2_Attack_Left::CDemonHunter_Female_CB2_Attack_Left()
{
	// StateType
	m_eStateType = STATE_TYPE_DEMONHUNTER_FEMALE_CB2_ATTACK_LEFT;

}

CDemonHunter_Female_CB2_Attack_Left::~CDemonHunter_Female_CB2_Attack_Left()
{
}

void CDemonHunter_Female_CB2_Attack_Left::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(13);
}

CPlayerState* CDemonHunter_Female_CB2_Attack_Left::Action()
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

		// FarAttack
		if(eSlotID == SLOT_ID_DEMONHUNTER_FAR_ATTACK)
		{
			if(m_pOwner->GetSlot(iSlotNum)->Begin(0) == SLOT_RESULT_NULL)
			{
				return new CDemonHunter_Female_CB2_Attack_Right;
			}
		}
		// EntanglingShot
		else if(eSlotID == SLOT_ID_DEMONHUNTER_ENTANGLING_SHOT)
		{
			if(m_pOwner->GetSlot(iSlotNum)->Begin(0) == SLOT_RESULT_NULL)
			{
				return new CDemonHunter_Female_CB2_Attack_Right;
			}
		}

		// HungeringArrow
		else if(eSlotID == SLOT_ID_DEMONHUNTER_HUNGERING_ARROW)
		{
			if(m_pOwner->GetSlot(iSlotNum)->Begin(0) == SLOT_RESULT_NULL)
			{
				return new CDemonHunter_Female_CB2_Attack_Right;
			}
		}

		// EvasiveFire
		else if(eSlotID == SLOT_ID_DEMONHUNTER_EVASIVE_FIRE)
		{
			if(m_pOwner->GetSlot(iSlotNum)->Begin(0) == SLOT_RESULT_NULL)
			{
				return new CDemonHunter_Female_CB2_Attack_Right;
			}
		}	
		return new CDemonHunter_Female_CB2_Idle;
	}

	return NULL;
}