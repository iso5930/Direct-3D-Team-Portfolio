#include "StdAfx.h"
#include "Monk_Male_DW_SF_Attack_L.h"

CMonk_Male_DW_SF_Attack_L::CMonk_Male_DW_SF_Attack_L(void)
{
	m_eStateType = STATE_TYPE_MONK_MALE_DW_SF_ATTACK_L;
}

CMonk_Male_DW_SF_Attack_L::~CMonk_Male_DW_SF_Attack_L(void)
{
}

void CMonk_Male_DW_SF_Attack_L::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(45);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CMonk_Male_DW_SF_Attack_L::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		// Find Priority Key and SlotNo
		int iSlotNum = CPlayerState::UsingKeyMouse();
		// If None Input..
		if(iSlotNum == -1)
			return new CMonk_Male_DW_SF_Idle;	

		if (MOUSE_OVER_TYPE_MONSTER == m_pOwner->GetPickType() && (m_pOwner->GetSlot(iSlotNum)->GetSlotID() == SLOT_ID_MONK_PUNCH || m_pOwner->GetSlot(iSlotNum)->GetSlotID() == SLOT_ID_MONK_NEAR_ATTACK) && (m_pOwner->GetSlot(iSlotNum)->Begin(0) == SLOT_RESULT_NULL))
		{
			return new CMonk_Male_DW_SF_Attack_R;
		}
		else
			return new CMonk_Male_DW_SF_Idle;				
	}
	return NULL;
}
