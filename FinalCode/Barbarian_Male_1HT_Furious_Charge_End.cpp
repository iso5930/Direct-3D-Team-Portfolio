#include "StdAfx.h"
#include "Barbarian_Male_1HT_Furious_Charge_End.h"

CBarbarian_Male_1HT_Furious_Charge_End::CBarbarian_Male_1HT_Furious_Charge_End(void)
{
	m_eStateType = STATE_TYPE_BARBARIAN_MALE_1HT_FURIOUS_CHARGE_END;
}

CBarbarian_Male_1HT_Furious_Charge_End::~CBarbarian_Male_1HT_Furious_Charge_End(void)
{
}

void CBarbarian_Male_1HT_Furious_Charge_End::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(76);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CBarbarian_Male_1HT_Furious_Charge_End::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CBarbarian_Male_1HT_Idle;	
	}
	return NULL;
}
