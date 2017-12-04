#include "StdAfx.h"
#include "Skeleton_King_Whirlwind_Start.h"

CSkeleton_King_Whirlwind_Start::CSkeleton_King_Whirlwind_Start(void)
{
	// StateType
	m_eStateType = STATE_TYPE_SKELETON_KING_WHIRLWIND_START;
}

CSkeleton_King_Whirlwind_Start::~CSkeleton_King_Whirlwind_Start(void)
{
}

void CSkeleton_King_Whirlwind_Start::Initialize()
{
	CMonsterState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(3);
}

CMonsterState* CSkeleton_King_Whirlwind_Start::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
		return new CSkeleton_King_Whirlwind_Loop;

	return NULL;
}