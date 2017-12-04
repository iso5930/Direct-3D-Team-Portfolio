#include "StdAfx.h"
#include "DemonHunter_Female_Buff.h"

CDemonHunter_Female_Buff::CDemonHunter_Female_Buff()
{
	// StateType
	m_eStateType = STATE_TYPE_DEMONHUNTER_FEMALE_BUFF;
}

CDemonHunter_Female_Buff::~CDemonHunter_Female_Buff()
{
}

void CDemonHunter_Female_Buff::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(41);
}

CPlayerState* CDemonHunter_Female_Buff::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CDemonHunter_Female_Idle;
	}
	return NULL;
}