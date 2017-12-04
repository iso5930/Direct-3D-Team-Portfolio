#include "StdAfx.h"
#include "Tristram_Jeweler_Idle.h"

CTristram_Jeweler_Idle::CTristram_Jeweler_Idle()
{
	// StateType
	m_eStateType = STATE_TYPE_TRISTRAM_JEWELER_IDLE;
}

CTristram_Jeweler_Idle::~CTristram_Jeweler_Idle()
{
}

void CTristram_Jeweler_Idle::Initialize()
{
	// Initialize
	CNPCState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(0);
}

CNPCState* CTristram_Jeweler_Idle::Action()
{
	return NULL;
}