#include "StdAfx.h"
#include "DemonHunter_Female_BigBow_Buff.h"

CDemonHunter_Female_BigBow_Buff::CDemonHunter_Female_BigBow_Buff()
{
	// StateType
	m_eStateType = STATE_TYPE_DEMONHUNTER_FEMALE_BIGBOW_BUFF;
}

CDemonHunter_Female_BigBow_Buff::~CDemonHunter_Female_BigBow_Buff()
{
}

void CDemonHunter_Female_BigBow_Buff::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(45);

}

CPlayerState* CDemonHunter_Female_BigBow_Buff::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CDemonHunter_Female_BigBow_Idle;
	}
	return NULL;
}