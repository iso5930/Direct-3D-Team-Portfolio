#include "StdAfx.h"
#include "Wizard_Female_1HS_AOE.h"

CBarbarian_Male_1HT_Knockback_End::CBarbarian_Male_1HT_Knockback_End(void)
{
	m_eStateType = STATE_TYPE_BARBARIAN_MALE_1HT_KNOCKBACK_END;
}

CBarbarian_Male_1HT_Knockback_End::~CBarbarian_Male_1HT_Knockback_End(void)
{
}

void CBarbarian_Male_1HT_Knockback_End::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(57);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CBarbarian_Male_1HT_Knockback_End::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CBarbarian_Male_1HT_Idle;	
	}
	return NULL;
}