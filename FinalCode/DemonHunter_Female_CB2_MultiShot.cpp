#include "StdAfx.h"
#include "DemonHunter_Female_CB2_MultiShot.h"

CDemonHunter_Female_CB2_MultiShot::CDemonHunter_Female_CB2_MultiShot()
{
	// StateType
	m_eStateType = STATE_TYPE_DEMONHUNTER_FEMALE_CB2_MULTISHOT;

}

CDemonHunter_Female_CB2_MultiShot::~CDemonHunter_Female_CB2_MultiShot()
{
}

void CDemonHunter_Female_CB2_MultiShot::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(26);
}

CPlayerState* CDemonHunter_Female_CB2_MultiShot::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CDemonHunter_Female_CB2_Idle;
	}

	return NULL;
}