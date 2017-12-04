#include "StdAfx.h"
#include "Skeleton_Shield_Brown_Spawn.h"

CSkeleton_Shield_Brown_Spawn::CSkeleton_Shield_Brown_Spawn(void)
{
	// StateType
	m_eStateType = STATE_TYPE_SKELETON_SHIELD_BROWN_SPAWN;
}

CSkeleton_Shield_Brown_Spawn::~CSkeleton_Shield_Brown_Spawn(void)
{
}

void CSkeleton_Shield_Brown_Spawn::Initialize()
{
	CMonsterState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(5);
}

CMonsterState* CSkeleton_Shield_Brown_Spawn::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
		return new CSkeleton_Shield_Brown_Idle;

	return NULL;
}