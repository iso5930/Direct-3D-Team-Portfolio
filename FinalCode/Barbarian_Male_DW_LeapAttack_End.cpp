#include "StdAfx.h"
#include "Barbarian_Male_DW_LeapAttack_End.h"

CBarbarian_Male_DW_LeapAttack_End::CBarbarian_Male_DW_LeapAttack_End(void)
{
	m_eStateType = STATE_TYPE_BARBARIAN_MALE_DW_LEAPATTACK_END;
}

CBarbarian_Male_DW_LeapAttack_End::~CBarbarian_Male_DW_LeapAttack_End(void)
{
}

void CBarbarian_Male_DW_LeapAttack_End::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(6);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CBarbarian_Male_DW_LeapAttack_End::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CBarbarian_Male_DW_Idle;	
	}
	return NULL;
}
