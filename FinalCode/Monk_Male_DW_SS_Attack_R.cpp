#include "StdAfx.h"
#include "Monk_Male_DW_SS_Attack_R.h"

CMonk_Male_DW_SS_Attack_R::CMonk_Male_DW_SS_Attack_R(void)
{
	m_eStateType = STATE_TYPE_MONK_MALE_DW_SS_ATTACK_R;
}

CMonk_Male_DW_SS_Attack_R::~CMonk_Male_DW_SS_Attack_R(void)
{
}

void CMonk_Male_DW_SS_Attack_R::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(42);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CMonk_Male_DW_SS_Attack_R::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		// Find Priority Key and SlotNo
		int iSlotNum = CPlayerState::UsingKeyMouse();
		// If None Input..
		if(iSlotNum == -1)
			return new CMonk_Male_DW_SS_Idle;	

		if (MOUSE_OVER_TYPE_MONSTER == m_pOwner->GetPickType() &&(m_pOwner->GetSlot(iSlotNum)->GetSlotID() == SLOT_ID_MONK_PUNCH || m_pOwner->GetSlot(iSlotNum)->GetSlotID() == SLOT_ID_MONK_NEAR_ATTACK) && (m_pOwner->GetSlot(iSlotNum)->Begin(0) == SLOT_RESULT_NULL))
		{
			return new CMonk_Male_DW_SS_Attack_L;
		}
		else
			return new CMonk_Male_DW_SS_Idle;			
	}
	return NULL;
}
