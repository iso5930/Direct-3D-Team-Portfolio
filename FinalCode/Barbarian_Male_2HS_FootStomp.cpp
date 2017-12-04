#include "StdAfx.h"
#include "Barbarian_Male_2HS_FootStomp.h"

CBarbarian_Male_2HS_FootStomp::CBarbarian_Male_2HS_FootStomp(void)
{
	m_eStateType = STATE_TYPE_BARBARIAN_MALE_2HS_FOOTSTOMP;
}

CBarbarian_Male_2HS_FootStomp::~CBarbarian_Male_2HS_FootStomp(void)
{
}

void CBarbarian_Male_2HS_FootStomp::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(81);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CBarbarian_Male_2HS_FootStomp::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CBarbarian_Male_2HS_Idle;	
	}
	return NULL;
}
