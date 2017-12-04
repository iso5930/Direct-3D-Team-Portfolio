#include "StdAfx.h"
#include "Butcher_Death.h"

CButcher_Death::CButcher_Death(void)
{
	// StateType
	m_eStateType = STATE_TYPE_BUTCHER_DEATH;
}

CButcher_Death::~CButcher_Death(void)
{
}

void CButcher_Death::Initialize()
{
	CMonsterState::Initialize();
	
	// SetAnimation
	m_pOwner->SetAnimation(12);
}

CMonsterState* CButcher_Death::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
		m_pOwner->Destroy();

	return NULL;
}
