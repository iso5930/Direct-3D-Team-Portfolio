#include "StdAfx.h"
#include "Butcher_Attack2.h"

CButcher_Attack2::CButcher_Attack2(void)
{
	// StateType
	m_eStateType = STATE_TYPE_BUTCHER_ATTACK2;

	// Mode
	m_iMode = 0;

	// Time
	m_fTime = 0.0f;
}

CButcher_Attack2::~CButcher_Attack2(void)
{
}

void CButcher_Attack2::Initialize()
{
	CMonsterState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(9);
}

CMonsterState* CButcher_Attack2::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
		return new CButcher_Idle;

	switch(m_iMode)
	{
	case 0:
		return Mode0();

	case 1:
		return Mode1();
	}

	return NULL;
}

CMonsterState* CButcher_Attack2::Mode0()
{
	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();
	if(m_fTime > 0.0f)
	{
		m_pOwner->CreateAttack();

		m_fTime = 0.0f;
		++m_iMode;
	}
	return NULL;
}

CMonsterState* CButcher_Attack2::Mode1()
{
	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();
	if(m_fTime > 1.0f)
	{
		m_pOwner->RemoveAttack();

		m_fTime = 0.0f;
		++m_iMode;
	}
	return NULL;
}
