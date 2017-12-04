#include "StdAfx.h"
#include "DemonHunter_Female_BigBow_Companion.h"

CDemonHunter_Female_BigBow_Companion::CDemonHunter_Female_BigBow_Companion()
{
	// StateType
	m_eStateType = STATE_TYPE_DEMONHUNTER_FEMALE_BIGBOW_COMPANION;
}

CDemonHunter_Female_BigBow_Companion::~CDemonHunter_Female_BigBow_Companion()
{
}

void CDemonHunter_Female_BigBow_Companion::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(32);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CDemonHunter_Female_BigBow_Companion::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CDemonHunter_Female_BigBow_Idle;
	}


	return NULL;
}