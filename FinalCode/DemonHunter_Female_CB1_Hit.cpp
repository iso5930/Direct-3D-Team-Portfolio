#include "StdAfx.h"
#include "DemonHunter_Female_CB1_Hit.h"

CDemonHunter_Female_CB1_Hit::CDemonHunter_Female_CB1_Hit()
{
	// StateType
	m_eStateType = STATE_TYPE_DEMONHUNTER_FEMALE_CB1_HIT;
}

CDemonHunter_Female_CB1_Hit::~CDemonHunter_Female_CB1_Hit()
{
}

void CDemonHunter_Female_CB1_Hit::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(47);
}

CPlayerState* CDemonHunter_Female_CB1_Hit::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CDemonHunter_Female_CB1_Idle;
	}
	return NULL;
}