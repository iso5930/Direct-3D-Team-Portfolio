#include "StdAfx.h"
#include "Butcher_Fan_Of_Chains.h"

CButcher_Fan_Of_Chains::CButcher_Fan_Of_Chains(void)
{
	// StateType
	m_eStateType = STATE_TYPE_BUTCHER_FAN_OF_CHAINS;
}

CButcher_Fan_Of_Chains::~CButcher_Fan_Of_Chains(void)
{
}

void CButcher_Fan_Of_Chains::Initialize()
{	
	CMonsterState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(10);
}

CMonsterState* CButcher_Fan_Of_Chains::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
		return new CButcher_Idle;

	return NULL;
}
