#include "StdAfx.h"
#include "Tristram_Arghus_Idle.h"

CTristram_Arghus_Idle::CTristram_Arghus_Idle()
{
	// StateType
	m_eStateType = STATE_TYPE_TRISTRAM_ARGHUS_IDLE;
}

CTristram_Arghus_Idle::~CTristram_Arghus_Idle()
{
}

void CTristram_Arghus_Idle::Initialize()
{
	// Initialize
	CNPCState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(0);
}

CNPCState* CTristram_Arghus_Idle::Action()
{
	return NULL;
}