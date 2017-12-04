#include "StdAfx.h"
#include "DemonHunter_Female_CB2_Hit.h"

CDemonHunter_Female_CB2_Hit::CDemonHunter_Female_CB2_Hit()
{
	// StateType
	m_eStateType = STATE_TYPE_DEMONHUNTER_FEMALE_CB2_HIT;
}

CDemonHunter_Female_CB2_Hit::~CDemonHunter_Female_CB2_Hit()
{
}

void CDemonHunter_Female_CB2_Hit::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(48);
}

CPlayerState* CDemonHunter_Female_CB2_Hit::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CDemonHunter_Female_CB2_Idle;
	}
	return NULL;
}