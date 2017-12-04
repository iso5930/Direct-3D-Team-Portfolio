#include "StdAfx.h"
#include "DemonHunter_Female_CB2_Companion.h"

CDemonHunter_Female_CB2_Companion::CDemonHunter_Female_CB2_Companion()
{
	// StateType
	m_eStateType = STATE_TYPE_DEMONHUNTER_FEMALE_CB2_COMPANION;
}

CDemonHunter_Female_CB2_Companion::~CDemonHunter_Female_CB2_Companion()
{
}

void CDemonHunter_Female_CB2_Companion::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(32);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CDemonHunter_Female_CB2_Companion::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CDemonHunter_Female_CB2_Idle;
	}
	return NULL;
}