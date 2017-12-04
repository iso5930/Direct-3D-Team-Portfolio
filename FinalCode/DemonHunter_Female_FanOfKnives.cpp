#include "StdAfx.h"
#include "DemonHunter_Female_FanOfKnives.h"

CDemonHunter_Female_FanOfKnives::CDemonHunter_Female_FanOfKnives()
{
	// StateType
	m_eStateType = STATE_TYPE_DEMONHUNTER_FEMALE_FANOFKNIVES;
}

CDemonHunter_Female_FanOfKnives::~CDemonHunter_Female_FanOfKnives()
{
}

void CDemonHunter_Female_FanOfKnives::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(29);
}

CPlayerState* CDemonHunter_Female_FanOfKnives::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CDemonHunter_Female_Idle;
	}

	return NULL;
}

