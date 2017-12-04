#include "StdAfx.h"
#include "DemonHunter_Female_WayPoint.h"

CDemonHunter_Female_WayPoint::CDemonHunter_Female_WayPoint()
{
	// StateType
	m_eStateType = STATE_TYPE_DEMONHUNTER_FEMALE_WAYPOINT;
}

CDemonHunter_Female_WayPoint::~CDemonHunter_Female_WayPoint()
{
}

void CDemonHunter_Female_WayPoint::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(40);
}

CPlayerState* CDemonHunter_Female_WayPoint::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CDemonHunter_Female_Idle;
	}

	return NULL;
}