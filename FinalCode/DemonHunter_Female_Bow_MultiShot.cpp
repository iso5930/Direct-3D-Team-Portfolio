#include "StdAfx.h"
#include "DemonHunter_Female_Bow_MultiShot.h"

CDemonHunter_Female_Bow_MultiShot::CDemonHunter_Female_Bow_MultiShot()
{
	// StateType
	m_eStateType = STATE_TYPE_DEMONHUNTER_FEMALE_BOW_MULTISHOT;
}

CDemonHunter_Female_Bow_MultiShot::~CDemonHunter_Female_Bow_MultiShot()
{
}

void CDemonHunter_Female_Bow_MultiShot::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(27);
}

CPlayerState* CDemonHunter_Female_Bow_MultiShot::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CDemonHunter_Female_Bow_Idle;
	}

	return NULL;
}