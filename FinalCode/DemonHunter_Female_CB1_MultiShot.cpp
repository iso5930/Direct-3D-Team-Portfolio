#include "StdAfx.h"
#include "DemonHunter_Female_CB1_MultiShot.h"

CDemonHunter_Female_CB1_MultiShot::CDemonHunter_Female_CB1_MultiShot()
{
	// StateType
	m_eStateType = STATE_TYPE_DEMONHUNTER_FEMALE_CB1_MULTISHOT;
}

CDemonHunter_Female_CB1_MultiShot::~CDemonHunter_Female_CB1_MultiShot()
{
}

void CDemonHunter_Female_CB1_MultiShot::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(25);
}

CPlayerState* CDemonHunter_Female_CB1_MultiShot::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CDemonHunter_Female_CB1_Idle;
	}

	return NULL;
}