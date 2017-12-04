#include "StdAfx.h"
#include "DemonHunter_Female_Attack2.h"

CDemonHunter_Female_Attack2::CDemonHunter_Female_Attack2()
{
	// StateType
	m_eStateType = STATE_TYPE_DEMONHUNTER_FEMALE_ATTACK2;

	// Mode
	m_iMode = 0;

	// Time
	m_fTime = 0.0f;
}

CDemonHunter_Female_Attack2::~CDemonHunter_Female_Attack2()
{
}

void CDemonHunter_Female_Attack2::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(11);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CDemonHunter_Female_Attack2::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
		return new CDemonHunter_Female_Idle;

	switch(m_iMode)
	{
	case 0:
		return Mode0();

	case 1:
		return Mode1();
	}

	return NULL;
}

CPlayerState* CDemonHunter_Female_Attack2::Mode0()
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

CPlayerState* CDemonHunter_Female_Attack2::Mode1()
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