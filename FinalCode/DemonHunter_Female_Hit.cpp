#include "StdAfx.h"
#include "DemonHunter_Female_Hit.h"

CDemonHunter_Female_Hit::CDemonHunter_Female_Hit()
{
	// StateType
	m_eStateType = STATE_TYPE_DEMONHUNTER_FEMALE_HIT;
}

CDemonHunter_Female_Hit::~CDemonHunter_Female_Hit()
{
}

void CDemonHunter_Female_Hit::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(46);
}

CPlayerState* CDemonHunter_Female_Hit::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CDemonHunter_Female_Idle;
	}


	return NULL;
}