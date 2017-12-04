#include "StdAfx.h"
#include "DemonHunter_Female_BigBow_Stunned.h"

CDemonHunter_Female_BigBow_Stunned::CDemonHunter_Female_BigBow_Stunned()
{
	// StateType
	m_eStateType = STATE_TYPE_DEMONHUNTER_FEMALE_BIGBOW_STUNNED;
}

CDemonHunter_Female_BigBow_Stunned::~CDemonHunter_Female_BigBow_Stunned()
{
}

void CDemonHunter_Female_BigBow_Stunned::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(39);
}

CPlayerState* CDemonHunter_Female_BigBow_Stunned::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CDemonHunter_Female_BigBow_Idle;
	}

	return NULL;
}