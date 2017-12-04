#include "StdAfx.h"
#include "Triune_Possessed_Hit.h"

CTriune_Possessed_Hit::CTriune_Possessed_Hit(void)
{
	// StateType
	m_eStateType = STATE_TYPE_TRIUNE_POSSESSED_HIT;
}

CTriune_Possessed_Hit::~CTriune_Possessed_Hit(void)
{
}

void CTriune_Possessed_Hit::Initialize()
{
	CMonsterState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(6);
}

CMonsterState* CTriune_Possessed_Hit::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
		return new CTriune_Possessed_Walk(2);

	return NULL;
}
