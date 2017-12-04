#include "StdAfx.h"
#include "Tristram_Mystic_Idle.h"

CTristram_Mystic_Idle::CTristram_Mystic_Idle()
{
	// StateType
	m_eStateType = STATE_TYPE_TRISTRAM_MYSTIC_IDLE;
}

CTristram_Mystic_Idle::~CTristram_Mystic_Idle()
{
}

void CTristram_Mystic_Idle::Initialize()
{
	// Initialize
	CNPCState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(0);
}

CNPCState* CTristram_Mystic_Idle::Action()
{
	return NULL;
}