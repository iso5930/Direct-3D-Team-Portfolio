#include "StdAfx.h"
#include "Skeleton_Shield_Red_Spawn.h"

CSkeleton_Shield_Red_Spawn::CSkeleton_Shield_Red_Spawn(void)
{
	// StateType
	m_eStateType = STATE_TYPE_SKELETON_SHIELD_RED_SPAWN;
}

CSkeleton_Shield_Red_Spawn::~CSkeleton_Shield_Red_Spawn(void)
{
}

void CSkeleton_Shield_Red_Spawn::Initialize()
{
	CMonsterState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(5);
}

CMonsterState* CSkeleton_Shield_Red_Spawn::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
		return new CSkeleton_Shield_Red_Idle;

	return NULL;
}