#include "StdAfx.h"
#include "Skeleton_Shield_Blue_Spawn.h"

CSkeleton_Shield_Blue_Spawn::CSkeleton_Shield_Blue_Spawn(void)
{
	// StateType
	m_eStateType = STATE_TYPE_SKELETON_SHIELD_BLUE_SPAWN;
}

CSkeleton_Shield_Blue_Spawn::~CSkeleton_Shield_Blue_Spawn(void)
{
}

void CSkeleton_Shield_Blue_Spawn::Initialize()
{
	CMonsterState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(5);
}

CMonsterState* CSkeleton_Shield_Blue_Spawn::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
		return new CSkeleton_Shield_Blue_Idle;

	return NULL;
}