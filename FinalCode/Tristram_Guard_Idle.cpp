#include "StdAfx.h"
#include "Tristram_Guard_Idle.h"

CTristram_Guard_Idle::CTristram_Guard_Idle()
{
	// StateType
	m_eStateType = STATE_TYPE_TRISTRAM_GUARD_IDLE;

	// Mode
	m_iMode = 0;

	// Time
	m_fTime = 0.0f;
}

CTristram_Guard_Idle::~CTristram_Guard_Idle()
{
}

void CTristram_Guard_Idle::Initialize()
{
	// Initialize
	CNPCState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(0);
}

CNPCState* CTristram_Guard_Idle::Action()
{
	switch(m_iMode)
	{
	case 0:
		return Mode0();

	case 1:
		return Mode1();
	}

	return NULL;
}

CNPCState* CTristram_Guard_Idle::Mode0()
{
	// Time
	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();
	if(m_fTime > 1.0f)
	{
		m_fTime = 0.0f;

		int iRand = rand() % 100;
		if(iRand > 50)
		{
			m_pOwner->SetAnimationMode(2);
			m_iMode = 1;
		}
	}

	return NULL;
}

CNPCState* CTristram_Guard_Idle::Mode1()
{
	// Time
	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();
	if(m_fTime > 0.5f)
	{
		m_fTime = 0.0f;

		m_pOwner->SetAnimationMode(0);
		m_iMode = 0;
	}

	return NULL;
}