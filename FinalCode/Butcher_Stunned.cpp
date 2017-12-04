#include "StdAfx.h"
#include "Butcher_Stunned.h"

CButcher_Stunned::CButcher_Stunned(void)
{
	// StateType
	m_eStateType = STATE_TYPE_BUTCHER_STUNNED;
}

CButcher_Stunned::~CButcher_Stunned(void)
{
}

void CButcher_Stunned::Initialize()
{
	CMonsterState::Initialize();
	
	// SetAnimation
	m_pOwner->SetAnimation(4);
}

CMonsterState* CButcher_Stunned::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
		return new CButcher_Walk;
	
	return NULL;
}
