#include "StdAfx.h"
#include "DemonHunter_Female_CB1_RainOfArrow.h"

CDemonHunter_Female_CB1_RainOfArrow::CDemonHunter_Female_CB1_RainOfArrow()
{
	// StateType
	m_eStateType = STATE_TYPE_DEMONHUNTER_FEMALE_CB1_RAINOFARROW;
}

CDemonHunter_Female_CB1_RainOfArrow::~CDemonHunter_Female_CB1_RainOfArrow()
{
}

void CDemonHunter_Female_CB1_RainOfArrow::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(21);
}

CPlayerState* CDemonHunter_Female_CB1_RainOfArrow::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CDemonHunter_Female_CB1_Idle;
	}

	return NULL;
}