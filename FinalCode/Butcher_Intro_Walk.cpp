#include "StdAfx.h"
#include "Butcher_Intro_Walk.h"

CButcher_Intro_Walk::CButcher_Intro_Walk(void)
{
	// StateType
	m_eStateType = STATE_TYPE_BUTCHER_INTRO_WALK;
}

CButcher_Intro_Walk::~CButcher_Intro_Walk(void)
{
}

void CButcher_Intro_Walk::Initialize()
{
	CMonsterState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(14);
}

CMonsterState* CButcher_Intro_Walk::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
		return new CButcher_Intro;

	return NULL;
}
