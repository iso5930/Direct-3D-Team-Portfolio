#include "StdAfx.h"
#include "DemonHunter_Female_CB2_Buff.h"

CDemonHunter_Female_CB2_Buff::CDemonHunter_Female_CB2_Buff()
{
	// StateType
	m_eStateType = STATE_TYPE_DEMONHUNTER_FEMALE_CB2_BUFF;
}

CDemonHunter_Female_CB2_Buff::~CDemonHunter_Female_CB2_Buff()
{
}

void CDemonHunter_Female_CB2_Buff::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(43);
}

CPlayerState* CDemonHunter_Female_CB2_Buff::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CDemonHunter_Female_CB2_Idle;
	}
	return NULL;
}