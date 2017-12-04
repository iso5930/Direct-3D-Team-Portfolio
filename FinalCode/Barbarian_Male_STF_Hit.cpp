#include "StdAfx.h"
#include "Barbarian_Male_STF_Hit.h"

CBarbarian_Male_STF_Hit::CBarbarian_Male_STF_Hit(void)
{
	m_eStateType = STATE_TYPE_BARBARIAN_MALE_STF_HIT;
}

CBarbarian_Male_STF_Hit::~CBarbarian_Male_STF_Hit(void)
{
}

void CBarbarian_Male_STF_Hit::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(61);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CBarbarian_Male_STF_Hit::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CBarbarian_Male_STF_Idle;	
	}
	return NULL;
}
