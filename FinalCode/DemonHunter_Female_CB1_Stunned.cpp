#include "StdAfx.h"
#include "DemonHunter_Female_CB1_Stunned.h"

CDemonHunter_Female_CB1_Stunned::CDemonHunter_Female_CB1_Stunned()
{
	// StateType
	m_eStateType = STATE_TYPE_DEMONHUNTER_FEMALE_CB1_STUNNED;
}

CDemonHunter_Female_CB1_Stunned::~CDemonHunter_Female_CB1_Stunned()
{
}

void CDemonHunter_Female_CB1_Stunned::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(36);
}

CPlayerState* CDemonHunter_Female_CB1_Stunned::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CDemonHunter_Female_CB1_Idle;
	}
	return NULL;
}