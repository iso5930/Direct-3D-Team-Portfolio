#include "StdAfx.h"
#include "DemonHunter_Female_Bow_RainOfArrow.h"

CDemonHunter_Female_Bow_RainOfArrow::CDemonHunter_Female_Bow_RainOfArrow()
{
	// StateType
	m_eStateType = STATE_TYPE_DEMONHUNTER_FEMALE_BOW_RAINOFARROW;
}

CDemonHunter_Female_Bow_RainOfArrow::~CDemonHunter_Female_Bow_RainOfArrow()
{
}

void CDemonHunter_Female_Bow_RainOfArrow::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(23);
}

CPlayerState* CDemonHunter_Female_Bow_RainOfArrow::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CDemonHunter_Female_Bow_Idle;
	}

	return NULL;
}