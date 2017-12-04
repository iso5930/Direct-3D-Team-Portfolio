#include "StdAfx.h"
#include "Butcher_Pull_Attack.h"

CButcher_Pull_Attack::CButcher_Pull_Attack(void)
{
	m_eStateType = STATE_TYPE_BUTCHER_PULL_ATTACK;
}

CButcher_Pull_Attack::~CButcher_Pull_Attack(void)
{
}

void CButcher_Pull_Attack::Initialize()
{
	CMonsterState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(7);
}

CMonsterState* CButcher_Pull_Attack::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
		return new CButcher_Idle;
	
	return NULL;
}
