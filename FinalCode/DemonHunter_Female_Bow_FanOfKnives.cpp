#include "StdAfx.h"
#include "DemonHunter_Female_Bow_FanOfKnives.h"

CDemonHunter_Female_Bow_FanOfKnives::CDemonHunter_Female_Bow_FanOfKnives()
{
	// StateType
	m_eStateType = STATE_TYPE_DEMONHUNTER_FEMALE_BOW_FANOFKNIVES;


}

CDemonHunter_Female_Bow_FanOfKnives::~CDemonHunter_Female_Bow_FanOfKnives()
{
}

void CDemonHunter_Female_Bow_FanOfKnives::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(29);
}

CPlayerState* CDemonHunter_Female_Bow_FanOfKnives::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
	
		return new CDemonHunter_Female_Bow_Idle;
	}

	return NULL;
}

