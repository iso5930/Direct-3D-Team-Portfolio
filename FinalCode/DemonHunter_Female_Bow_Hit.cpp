#include "StdAfx.h"
#include "DemonHunter_Female_Bow_Hit.h"

CDemonHunter_Female_Bow_Hit::CDemonHunter_Female_Bow_Hit()
{
	// StateType
	m_eStateType = STATE_TYPE_DEMONHUNTER_FEMALE_BOW_HIT;
}

CDemonHunter_Female_Bow_Hit::~CDemonHunter_Female_Bow_Hit()
{
}

void CDemonHunter_Female_Bow_Hit::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(49);
}

CPlayerState* CDemonHunter_Female_Bow_Hit::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CDemonHunter_Female_Bow_Idle;
	}

	return NULL;
}