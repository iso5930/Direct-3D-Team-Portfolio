#include "StdAfx.h"
#include "DemonHunter_Female_BigBow_Caltrop.h"

CDemonHunter_Female_BigBow_Caltrop::CDemonHunter_Female_BigBow_Caltrop()
{
	// StateType
	m_eStateType = STATE_TYPE_DEMONHUNTER_FEMALE_BIGBOW_CALTROP;
}

CDemonHunter_Female_BigBow_Caltrop::~CDemonHunter_Female_BigBow_Caltrop()
{

}

void CDemonHunter_Female_BigBow_Caltrop::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(31);

	// Clear
	m_pPathFindCom->Clear();

	KeyMouseStop(m_pOwner->GetLastPushSlotNum());
}

CPlayerState* CDemonHunter_Female_BigBow_Caltrop::Action()
{
	if(m_pAnimController->m_dFrameTime -0.2 <= m_pAnimController->GetTrackPos())
	{
		return new CDemonHunter_Female_BigBow_Idle;
	}
	


	return NULL;
}