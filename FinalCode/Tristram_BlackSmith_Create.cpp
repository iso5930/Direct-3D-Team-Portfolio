#include "StdAfx.h"
#include "Tristram_BlackSmith_Create.h"

CTristram_BlackSmith_Create::CTristram_BlackSmith_Create()
{
	// StateType
	m_eStateType = STATE_TYPE_TRISTRAM_BLACKSMITH_CREATE;

	// Time
	m_fTime = 0.0f;
}

CTristram_BlackSmith_Create::~CTristram_BlackSmith_Create()
{
}

void CTristram_BlackSmith_Create::Initialize()
{
	// Initialize
	CNPCState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(1);
}

CNPCState* CTristram_BlackSmith_Create::Action()
{
	// Time
	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();
	if(m_fTime > 4.8f)
		return new CTristram_BlackSmith_Idle;

	return NULL;
}