#include "StdAfx.h"
#include "Butcher_Chain_In.h"

CButcher_Chain_In::CButcher_Chain_In(void)
{
	m_eStateType = STATE_TYPE_BUTCHER_CHAIN_IN;
}

CButcher_Chain_In::~CButcher_Chain_In(void)
{
}

void CButcher_Chain_In::Initialize()
{
	CMonsterState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(5);
}

CMonsterState* CButcher_Chain_In::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
		return new CButcher_Chain_Out;

	return NULL;
}
