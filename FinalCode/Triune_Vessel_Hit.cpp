#include "StdAfx.h"
#include "Triune_Vessel_Hit.h"

CTriune_Vessel_Hit::CTriune_Vessel_Hit(void)
{
	// StateType
	m_eStateType = STATE_TYPE_TRIUNE_VESSEL_HIT;
}

CTriune_Vessel_Hit::~CTriune_Vessel_Hit(void)
{
}

void CTriune_Vessel_Hit::Initialize()
{
	CMonsterState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(4);
}

CMonsterState* CTriune_Vessel_Hit::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
		return new CTriune_Vessel_Activating;

	return NULL;
}
