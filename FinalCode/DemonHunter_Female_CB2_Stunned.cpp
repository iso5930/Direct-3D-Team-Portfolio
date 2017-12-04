#include "StdAfx.h"
#include "DemonHunter_Female_CB2_Stunned.h"

CDemonHunter_Female_CB2_Stunned::CDemonHunter_Female_CB2_Stunned()
{
	// StateType
	m_eStateType = STATE_TYPE_DEMONHUNTER_FEMALE_CB2_STUNNED;
}

CDemonHunter_Female_CB2_Stunned::~CDemonHunter_Female_CB2_Stunned()
{
}

void CDemonHunter_Female_CB2_Stunned::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(37);
}

CPlayerState* CDemonHunter_Female_CB2_Stunned::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CDemonHunter_Female_CB2_Idle;
	}
	return NULL;
}