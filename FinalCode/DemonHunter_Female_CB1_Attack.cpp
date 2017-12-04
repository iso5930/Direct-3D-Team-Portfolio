#include "StdAfx.h"
#include "DemonHunter_Female_CB1_Attack.h"

CDemonHunter_Female_CB1_Attack::CDemonHunter_Female_CB1_Attack()
{
	// StateType
	m_eStateType = STATE_TYPE_DEMONHUNTER_FEMALE_CB1_ATTACK;
}

CDemonHunter_Female_CB1_Attack::~CDemonHunter_Female_CB1_Attack()
{
}

void CDemonHunter_Female_CB1_Attack::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(12);
}

CPlayerState* CDemonHunter_Female_CB1_Attack::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CDemonHunter_Female_CB1_Idle;
	}
	
	return NULL;
}