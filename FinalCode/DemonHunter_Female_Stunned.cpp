#include "StdAfx.h"
#include "DemonHunter_Female_Stunned.h"

CDemonHunter_Female_Stunned::CDemonHunter_Female_Stunned()
{
	// StateType
	m_eStateType = STATE_TYPE_DEMONHUNTER_FEMALE_STUNNED;
}

CDemonHunter_Female_Stunned::~CDemonHunter_Female_Stunned()
{
}

void CDemonHunter_Female_Stunned::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(35);
}

CPlayerState* CDemonHunter_Female_Stunned::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CDemonHunter_Female_Idle;

	}

	return NULL;
}