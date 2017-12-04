#include "StdAfx.h"
#include "Skeleton_Archer_Red_Spawn.h"

CSkeleton_Archer_Red_Spawn::CSkeleton_Archer_Red_Spawn(void)
{
	// StateType
	m_eStateType = STATE_TYPE_SKELETON_ARCHER_BROWN_SPAWN;

}

CSkeleton_Archer_Red_Spawn::~CSkeleton_Archer_Red_Spawn(void)
{

}

void CSkeleton_Archer_Red_Spawn::Initialize()
{
	CMonsterState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(6);
}

CMonsterState* CSkeleton_Archer_Red_Spawn::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
		return new CSkeleton_Archer_Brown_Idle(0);

	return NULL;
}
