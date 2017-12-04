#include "StdAfx.h"
#include "Barbarian_male_STF_Parry.h"

CBarbarian_Male_STF_Parry::CBarbarian_Male_STF_Parry(void)
{
	m_eStateType = STATE_TYPE_BARBARIAN_MALE_STF_PARRY;
}

CBarbarian_Male_STF_Parry::~CBarbarian_Male_STF_Parry(void)
{
}

void CBarbarian_Male_STF_Parry::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(43);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CBarbarian_Male_STF_Parry::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CBarbarian_Male_STF_Idle;	
	}
	return NULL;
}