#include "StdAfx.h"
#include "Barbarian_Male_1HT_HirlWind_End.h"

CBarbarian_Male_1HT_HirlWind_End::CBarbarian_Male_1HT_HirlWind_End(void)
{
	m_eStateType = STATE_TYPE_BARBARIAN_MALE_1HT_HIRLWIND_END;
}

CBarbarian_Male_1HT_HirlWind_End::~CBarbarian_Male_1HT_HirlWind_End(void)
{
}

void CBarbarian_Male_1HT_HirlWind_End::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(22);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CBarbarian_Male_1HT_HirlWind_End::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CBarbarian_Male_1HT_Idle;	
	}
	return NULL;
}
