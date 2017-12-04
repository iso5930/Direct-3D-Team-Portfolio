#include "StdAfx.h"
#include "Butcher_Phase_Change.h"

CButcher_Phase_Change::CButcher_Phase_Change(void)
{
	// StateType
	m_eStateType = STATE_TYPE_BUTCHER_PHASE_CHANGE;
}

CButcher_Phase_Change::~CButcher_Phase_Change(void)
{
}

void CButcher_Phase_Change::Initialize()
{
	CMonsterState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(15);
}

CMonsterState* CButcher_Phase_Change::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
		return new CButcher_Idle;

	return NULL;
}
