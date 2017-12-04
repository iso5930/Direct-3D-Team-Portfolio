#include "StdAfx.h"
#include "Skeleton_King_Whirlwind_End.h"

CSkeleton_King_Whirlwind_End::CSkeleton_King_Whirlwind_End(void)
{
	// StateType
	m_eStateType = STATE_TYPE_SKELETON_KING_WHIRLWIND_END;
}

CSkeleton_King_Whirlwind_End::~CSkeleton_King_Whirlwind_End(void)
{
}

void CSkeleton_King_Whirlwind_End::Initialize()
{
	CMonsterState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(5);
}

CMonsterState* CSkeleton_King_Whirlwind_End::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
		return new CSkeleton_King_Idle(0);

	return NULL;
}
