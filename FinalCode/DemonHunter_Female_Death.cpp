#include "StdAfx.h"
#include "DemonHunter_Female_Death.h"

CDemonHunter_Female_Death::CDemonHunter_Female_Death()
{
	// StateType
	m_eStateType = STATE_TYPE_DEMONHUNTER_FEMALE_DEATH;
}

CDemonHunter_Female_Death::~CDemonHunter_Female_Death()
{
}

void CDemonHunter_Female_Death::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(51);
}

CPlayerState* CDemonHunter_Female_Death::Action()
{
	return NULL;
}