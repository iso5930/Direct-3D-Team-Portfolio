#include "StdAfx.h"
#include "DemonHunter_Female_BigBow_Attack.h"

CDemonHunter_Female_BigBow_Attack::CDemonHunter_Female_BigBow_Attack()
{
	// StateType
	m_eStateType = STATE_TYPE_DEMONHUNTER_FEMALE_BIGBOW_ATTACK;


}

CDemonHunter_Female_BigBow_Attack::~CDemonHunter_Female_BigBow_Attack()
{
}

void CDemonHunter_Female_BigBow_Attack::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(16);
}

CPlayerState* CDemonHunter_Female_BigBow_Attack::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CDemonHunter_Female_BigBow_Idle;
	}

	return NULL;
}