#include "StdAfx.h"
#include "Tristram_Tashun_Idle.h"

CTristram_Tashun_Idle::CTristram_Tashun_Idle()
{
	// StateType
	m_eStateType = STATE_TYPE_TRISTRAM_TASHUN_IDLE;
}

CTristram_Tashun_Idle::~CTristram_Tashun_Idle()
{
}

void CTristram_Tashun_Idle::Initialize()
{
	// Initialize
	CNPCState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(0);
}

CNPCState* CTristram_Tashun_Idle::Action()
{
	return NULL;
}