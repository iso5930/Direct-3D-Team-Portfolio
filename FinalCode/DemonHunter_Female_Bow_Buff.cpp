#include "StdAfx.h"
#include "DemonHunter_Female_Bow_Buff.h"

CDemonHunter_Female_Bow_Buff::CDemonHunter_Female_Bow_Buff()
{
	// StateType
	m_eStateType = STATE_TYPE_DEMONHUNTER_FEMALE_BOW_BUFF;
}

CDemonHunter_Female_Bow_Buff::~CDemonHunter_Female_Bow_Buff()
{
}

void CDemonHunter_Female_Bow_Buff::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(44);
}

CPlayerState* CDemonHunter_Female_Bow_Buff::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CDemonHunter_Female_Bow_Idle;
	}


	return NULL;
}