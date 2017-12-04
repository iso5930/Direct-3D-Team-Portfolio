#include "StdAfx.h"
#include "Skeleton_King_Intro_Idle.h"

CSkeleton_King_Intro_Idle::CSkeleton_King_Intro_Idle(void)
{
	// StateType
	m_eStateType = STATE_TYPE_SKELETON_KING_INTRO_IDLE;
}

CSkeleton_King_Intro_Idle::~CSkeleton_King_Intro_Idle(void)
{
}

void CSkeleton_King_Intro_Idle::Initialize()
{
	CMonsterState::Initialize();
	
	// SetAnimation
	m_pOwner->SetAnimation(13);
}

CMonsterState* CSkeleton_King_Intro_Idle::Action()
{
	m_pOwner->RemoveComponent(COM_TYPE_COLLISION);

	if(m_pOwner->IsOver())
		return new CSkeleton_King_Intro;

	return NULL;
}
