#include "StdAfx.h"
#include "Butcher_Intro.h"

CButcher_Intro::CButcher_Intro(void)
{
	// StateType
	m_eStateType = STATE_TYPE_BUTCHER_INTRO;
}

CButcher_Intro::~CButcher_Intro(void)
{
}

void CButcher_Intro::Initialize()
{
	CMonsterState::Initialize();
	
	// SetAnimation
	m_pOwner->SetAnimation(13);
}

CMonsterState* CButcher_Intro::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
		return new CButcher_Phase_Change;

	return NULL;
}
