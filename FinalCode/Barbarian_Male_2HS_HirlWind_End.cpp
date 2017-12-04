#include "StdAfx.h"
#include "Barbarian_Male_2HS_HirlWind_End.h"

CBarbarian_Male_2HS_HirlWind_End::CBarbarian_Male_2HS_HirlWind_End(void)
{
	m_eStateType = STATE_TYPE_WIZARD_FEMALE_2HS_AOE;
}

CBarbarian_Male_2HS_HirlWind_End::~CBarbarian_Male_2HS_HirlWind_End(void)
{
}

void CBarbarian_Male_2HS_HirlWind_End::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(21);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CBarbarian_Male_2HS_HirlWind_End::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CBarbarian_Male_2HS_Idle;	
	}
	return NULL;
}
