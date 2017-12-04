#include "StdAfx.h"
#include "DemonHunter_Female_Impale.h"

CDemonHunter_Female_Impale::CDemonHunter_Female_Impale()
{
	// StateType
	m_eStateType = STATE_TYPE_DEMONHUNTER_FEMALE_IMPALE;

}

CDemonHunter_Female_Impale::~CDemonHunter_Female_Impale()
{
}

void CDemonHunter_Female_Impale::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(30);
}

CPlayerState* CDemonHunter_Female_Impale::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CDemonHunter_Female_Idle;
	}

	return NULL;
}