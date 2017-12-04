#include "StdAfx.h"
#include "Barbarian_Male_2HS_Hit.h"

CBarbarian_Male_2HS_Hit::CBarbarian_Male_2HS_Hit(void)
{
	m_eStateType = STATE_TYPE_BARBARIAN_MALE_2HS_HIT;
}

CBarbarian_Male_2HS_Hit::~CBarbarian_Male_2HS_Hit(void)
{
}

void CBarbarian_Male_2HS_Hit::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(63);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CBarbarian_Male_2HS_Hit::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CBarbarian_Male_2HS_Idle;	
	}
	return NULL;
}
