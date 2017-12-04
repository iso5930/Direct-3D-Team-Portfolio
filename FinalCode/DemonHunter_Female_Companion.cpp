#include "StdAfx.h"
#include "DemonHunter_Female_Companion.h"

CDemonHunter_Female_Companion::CDemonHunter_Female_Companion()
{
	// StateType
	m_eStateType = STATE_TYPE_DEMONHUNTER_FEMALE_COMPANION;
}

CDemonHunter_Female_Companion::~CDemonHunter_Female_Companion()
{
}

void CDemonHunter_Female_Companion::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(32);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CDemonHunter_Female_Companion::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CDemonHunter_Female_Idle;
	}
	return NULL;
}