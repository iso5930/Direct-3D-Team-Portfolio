#include "StdAfx.h"
#include "DemonHunter_Female_Bow_Companion.h"

CDemonHunter_Female_Bow_Companion::CDemonHunter_Female_Bow_Companion()
{
	// StateType
	m_eStateType = STATE_TYPE_DEMONHUNTER_FEMALE_BOW_COMPANION;
}

CDemonHunter_Female_Bow_Companion::~CDemonHunter_Female_Bow_Companion()
{
}

void CDemonHunter_Female_Bow_Companion::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(32);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CDemonHunter_Female_Bow_Companion::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CDemonHunter_Female_Bow_Idle;
	}

	return NULL;
}