#include "StdAfx.h"
#include "DemonHunter_Female_CB1_Companion.h"

CDemonHunter_Female_CB1_Companion::CDemonHunter_Female_CB1_Companion()
{
	// StateType
	m_eStateType = STATE_TYPE_DEMONHUNTER_FEMALE_CB1_COMPANION;
}

CDemonHunter_Female_CB1_Companion::~CDemonHunter_Female_CB1_Companion()
{
}

void CDemonHunter_Female_CB1_Companion::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(32);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CDemonHunter_Female_CB1_Companion::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CDemonHunter_Female_CB1_Idle;
	}
	return NULL;
}