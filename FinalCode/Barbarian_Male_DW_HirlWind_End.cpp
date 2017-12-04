#include "StdAfx.h"
#include "Barbarian_male_DW_HirlWind_End.h"

CBarbarian_male_DW_HirlWind_End::CBarbarian_male_DW_HirlWind_End(void)
{
	m_eStateType = STATE_TYPE_BARBARIAN_MALE_DW_HIRLWIND_END;
}

CBarbarian_male_DW_HirlWind_End::~CBarbarian_male_DW_HirlWind_End(void)
{
}

void CBarbarian_male_DW_HirlWind_End::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(18);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CBarbarian_male_DW_HirlWind_End::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CBarbarian_Male_DW_Idle;	
	}
	return NULL;
}
