#include "StdAfx.h"
#include "DemonHunter_Female_CB2_RainOfArrow.h"

CDemonHunter_Female_CB2_RainOfArrow::CDemonHunter_Female_CB2_RainOfArrow()
{
	// StateType
	m_eStateType = STATE_TYPE_DEMONHUNTER_FEMALE_CB2_RAINOFARROW;

}

CDemonHunter_Female_CB2_RainOfArrow::~CDemonHunter_Female_CB2_RainOfArrow()
{
}

void CDemonHunter_Female_CB2_RainOfArrow::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(22);
}

CPlayerState* CDemonHunter_Female_CB2_RainOfArrow::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CDemonHunter_Female_CB2_Idle;
	}

	return NULL;
}