#include "StdAfx.h"
#include "DemonHunter_Female_BigBow_MultiShot.h"

CDemonHunter_Female_BigBow_MultiShot::CDemonHunter_Female_BigBow_MultiShot()
{
	// StateType
	m_eStateType = STATE_TYPE_DEMONHUNTER_FEMALE_BIGBOW_MULTISHOT;

}

CDemonHunter_Female_BigBow_MultiShot::~CDemonHunter_Female_BigBow_MultiShot()
{
}

void CDemonHunter_Female_BigBow_MultiShot::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(28);
}

CPlayerState* CDemonHunter_Female_BigBow_MultiShot::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CDemonHunter_Female_BigBow_Idle;
	}


	return NULL;
}