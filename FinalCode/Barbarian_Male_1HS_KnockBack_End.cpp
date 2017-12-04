#include "StdAfx.h"
#include "Barbarian_Male_1HS_Knockback_End.h"

CBarbarian_Male_1HS_Knockback_End::CBarbarian_Male_1HS_Knockback_End(void)
{
	m_eStateType = STATE_TYPE_BARBARIAN_MALE_1HS_KNOCKBACK_END;
}

CBarbarian_Male_1HS_Knockback_End::~CBarbarian_Male_1HS_Knockback_End(void)
{
}

void CBarbarian_Male_1HS_Knockback_End::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(59);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CBarbarian_Male_1HS_Knockback_End::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CBarbarian_Male_1HS_Idle;	
	}
	return NULL;
}
