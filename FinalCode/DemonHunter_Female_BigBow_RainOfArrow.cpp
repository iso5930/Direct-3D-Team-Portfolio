#include "StdAfx.h"
#include "DemonHunter_Female_BigBow_RainOfArrow.h"

CDemonHunter_Female_BigBow_RainOfArrow::CDemonHunter_Female_BigBow_RainOfArrow()
{
	// StateType
	m_eStateType = STATE_TYPE_DEMONHUNTER_FEMALE_BIGBOW_RAINOFARROW;

}

CDemonHunter_Female_BigBow_RainOfArrow::~CDemonHunter_Female_BigBow_RainOfArrow()
{
}

void CDemonHunter_Female_BigBow_RainOfArrow::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(24);
}

CPlayerState* CDemonHunter_Female_BigBow_RainOfArrow::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CDemonHunter_Female_BigBow_Idle;
	}

	return NULL;
}