#include "StdAfx.h"
#include "DemonHunter_Female_Caltrop.h"

CDemonHunter_Female_Caltrop::CDemonHunter_Female_Caltrop()
{
	// StateType
	m_eStateType = STATE_TYPE_DEMONHUNTER_FEMALE_CALTROP;
}

CDemonHunter_Female_Caltrop::~CDemonHunter_Female_Caltrop()
{
}

void CDemonHunter_Female_Caltrop::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(31);

	// Clear
	m_pPathFindCom->Clear();

	KeyMouseStop(m_pOwner->GetLastPushSlotNum());
}

CPlayerState* CDemonHunter_Female_Caltrop::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.2 <= m_pAnimController->GetTrackPos())
	{
		return new CDemonHunter_Female_Idle;
	}

	return NULL;
}