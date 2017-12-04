#include "StdAfx.h"
#include "Tristram_Jeweler_Talk.h"

CTristram_Jeweler_Talk::CTristram_Jeweler_Talk()
{
	// StateType
	m_eStateType = STATE_TYPE_TRISTRAM_JEWELER_TALK;
}

CTristram_Jeweler_Talk::~CTristram_Jeweler_Talk()
{
}

void CTristram_Jeweler_Talk::Initialize()
{
	// Initialize
	CNPCState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(1);
}

CNPCState* CTristram_Jeweler_Talk::Action()
{
	return NULL;
}