#include "StdAfx.h"
#include "Barbarian_Male_1HS_Hit.h"

CBarbarian_Male_1HS_Hit::CBarbarian_Male_1HS_Hit(void)
{
	m_eStateType = STATE_TYPE_BARBARIAN_MALE_1HS_HIT;
}

CBarbarian_Male_1HS_Hit::~CBarbarian_Male_1HS_Hit(void)
{
}

void CBarbarian_Male_1HS_Hit::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(65);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CBarbarian_Male_1HS_Hit::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CBarbarian_Male_1HS_Idle;	
	}
	return NULL;
}
