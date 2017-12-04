#include "StdAfx.h"
#include "Barbarian_Male_2HT_Furious_Charge_End.h"

CBarbarian_Male_2HT_Furious_Charge_End::CBarbarian_Male_2HT_Furious_Charge_End(void)
{
	m_eStateType = STATE_TYPE_BARBARIAN_MALE_2HT_FURIOUS_CHARGE_END;
}

CBarbarian_Male_2HT_Furious_Charge_End::~CBarbarian_Male_2HT_Furious_Charge_End(void)
{
}

void CBarbarian_Male_2HT_Furious_Charge_End::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(74);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CBarbarian_Male_2HT_Furious_Charge_End::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CBarbarian_Male_2HT_Idle;	
	}
	return NULL;
}
