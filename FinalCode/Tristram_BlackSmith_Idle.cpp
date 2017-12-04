#include "StdAfx.h"
#include "Tristram_BlackSmith_Idle.h"

CTristram_BlackSmith_Idle::CTristram_BlackSmith_Idle()
{
	// StateType
	m_eStateType = STATE_TYPE_TRISTRAM_BLACKSMITH_IDLE;

	// Time
	m_fTime = 0.0f;
}

CTristram_BlackSmith_Idle::~CTristram_BlackSmith_Idle()
{
}

void CTristram_BlackSmith_Idle::Initialize()
{
	// Initialize
	CNPCState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(0);
}

CNPCState* CTristram_BlackSmith_Idle::Action()
{
	// Time
	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();
	if(m_fTime > 10.0f)
	{
		m_fTime = 0.0f;

		int iRand = rand() % 100;
		if(iRand > 80)
			return new CTristram_BlackSmith_Create;	
	}

	return NULL;
}