#include "StdAfx.h"
#include "DemonHunter_Female_BigBow_Hit.h"

CDemonHunter_Female_BigBow_Hit::CDemonHunter_Female_BigBow_Hit()
{
	// StateType
	m_eStateType = STATE_TYPE_DEMONHUNTER_FEMALE_BIGBOW_HIT;
}

CDemonHunter_Female_BigBow_Hit::~CDemonHunter_Female_BigBow_Hit()
{
}

void CDemonHunter_Female_BigBow_Hit::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(50);
}

CPlayerState* CDemonHunter_Female_BigBow_Hit::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CDemonHunter_Female_BigBow_Idle;
	}


	return NULL;
}