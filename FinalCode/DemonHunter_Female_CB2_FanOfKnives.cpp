#include "StdAfx.h"
#include "DemonHunter_Female_CB2_FanOfKnives.h"

CDemonHunter_Female_CB2_FanOfKnives::CDemonHunter_Female_CB2_FanOfKnives()
{
	// StateType
	m_eStateType = STATE_TYPE_DEMONHUNTER_FEMALE_CB2_FANOFKNIVES;

}

CDemonHunter_Female_CB2_FanOfKnives::~CDemonHunter_Female_CB2_FanOfKnives()
{
}

void CDemonHunter_Female_CB2_FanOfKnives::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(29);
}

CPlayerState* CDemonHunter_Female_CB2_FanOfKnives::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CDemonHunter_Female_CB2_Idle;
	}

	return NULL;
}

