#include "StdAfx.h"
#include "Barbarian_Male_STF_Knockback_End.h"

CBarbarian_Male_STF_Knockback_End::CBarbarian_Male_STF_Knockback_End(void)
{
	m_eStateType = STATE_TYPE_BARBARIAN_MALE_STF_KNOCKBACK_END;
}

CBarbarian_Male_STF_Knockback_End::~CBarbarian_Male_STF_Knockback_End(void)
{
}

void CBarbarian_Male_STF_Knockback_End::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(55);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CBarbarian_Male_STF_Knockback_End::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CWizard_Female_STF_Idle;	
	}
	return NULL;
}
