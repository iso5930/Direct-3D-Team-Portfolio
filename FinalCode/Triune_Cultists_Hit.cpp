#include "StdAfx.h"
#include "Triune_Cultists_Hit.h"

CTriune_Cultists_Hit::CTriune_Cultists_Hit(void)
{
	// StateType
	m_eStateType = STATE_TYPE_TRIUNE_CULTISTS_HIT;
}

CTriune_Cultists_Hit::~CTriune_Cultists_Hit(void)
{
}

void CTriune_Cultists_Hit::Initialize()
{
	CMonsterState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(4);
}

CMonsterState* CTriune_Cultists_Hit::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
		return new CTriune_Cultists_Run(1);

	return NULL;
}
