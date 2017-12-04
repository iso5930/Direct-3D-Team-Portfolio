#include "StdAfx.h"
#include "DemonHunter_Female_Bow_Attack.h"

CDemonHunter_Female_Bow_Attack::CDemonHunter_Female_Bow_Attack()
{
	// StateType
	m_eStateType = STATE_TYPE_DEMONHUNTER_FEMALE_BOW_ATTACK;
}

CDemonHunter_Female_Bow_Attack::~CDemonHunter_Female_Bow_Attack()
{
}

void CDemonHunter_Female_Bow_Attack::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(15);
}

CPlayerState* CDemonHunter_Female_Bow_Attack::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CDemonHunter_Female_Bow_Idle;
	}

	return NULL;
}