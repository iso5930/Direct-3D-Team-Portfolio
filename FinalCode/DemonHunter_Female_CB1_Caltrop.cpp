#include "StdAfx.h"
#include "DemonHunter_Female_CB1_Caltrop.h"

CDemonHunter_Female_CB1_Caltrop::CDemonHunter_Female_CB1_Caltrop()
{
	// StateType
	m_eStateType = STATE_TYPE_DEMONHUNTER_FEMALE_CB1_CALTROP;
}

CDemonHunter_Female_CB1_Caltrop::~CDemonHunter_Female_CB1_Caltrop()
{
}

void CDemonHunter_Female_CB1_Caltrop::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(31);

	// Clear
	m_pPathFindCom->Clear();

	KeyMouseStop(m_pOwner->GetLastPushSlotNum());
}

CPlayerState* CDemonHunter_Female_CB1_Caltrop::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.2 <= m_pAnimController->GetTrackPos())
	{
		return new CDemonHunter_Female_CB1_Idle;
	}

	return NULL;
}