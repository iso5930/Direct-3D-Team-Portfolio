#include "StdAfx.h"
#include "DemonHunter_Female_CB2_Impale.h"

CDemonHunter_Female_CB2_Impale::CDemonHunter_Female_CB2_Impale()
{
	// StateType
	m_eStateType = STATE_TYPE_DEMONHUNTER_FEMALE_CB2_IMPALE;
}

CDemonHunter_Female_CB2_Impale::~CDemonHunter_Female_CB2_Impale()
{
}

void CDemonHunter_Female_CB2_Impale::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(30);
}

CPlayerState* CDemonHunter_Female_CB2_Impale::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CDemonHunter_Female_CB2_Idle;
	}

	return NULL;
}