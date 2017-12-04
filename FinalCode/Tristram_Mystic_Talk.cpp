#include "StdAfx.h"
#include "Tristram_Mystic_Talk.h"

CTristram_Mystic_Talk::CTristram_Mystic_Talk()
{
	// StateType
	m_eStateType = STATE_TYPE_TRISTRAM_MYSTIC_TALK;
}

CTristram_Mystic_Talk::~CTristram_Mystic_Talk()
{
}

void CTristram_Mystic_Talk::Initialize()
{
	// Initialize
	CNPCState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(1);
}

CNPCState* CTristram_Mystic_Talk::Action()
{
	return NULL;
}