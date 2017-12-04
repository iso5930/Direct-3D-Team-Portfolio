#include "StdAfx.h"
#include "Warden_Attack1.h"

CWarden_Attack1::CWarden_Attack1(void)
{
	// StateType
	m_eStateType = STATE_TYPE_WARDEN_ATTACK1;

	// Mode
	m_iMode = 0;

	// Time
	m_fTime = 0.0f;
}

CWarden_Attack1::~CWarden_Attack1(void)
{
}

void CWarden_Attack1::Initialize()
{
	CMonsterState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(2);
}

CMonsterState* CWarden_Attack1::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
		return new CWarden_Run(1);

	switch(m_iMode)
	{
	case 0:
		return Mode0();

	case 1:
		return Mode1();
	}

	return NULL;
}

CMonsterState* CWarden_Attack1::Mode0()
{
	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();
	if(m_fTime > 0.3f)
	{
		m_pOwner->CreateAttack();

		m_fTime = 0.0f;
		++m_iMode;
	}
	
	return NULL;
}

CMonsterState* CWarden_Attack1::Mode1()
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