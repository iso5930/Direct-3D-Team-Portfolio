#include "StdAfx.h"
#include "Skeleton_Axe_Red_Spawn.h"

CSkeleton_Axe_Red_Spawn::CSkeleton_Axe_Red_Spawn(void)
{
	// StateType
	m_eStateType = STATE_TYPE_SKELETON_AXE_RED_SPAWN;
}

CSkeleton_Axe_Red_Spawn::~CSkeleton_Axe_Red_Spawn(void)
{

}

void CSkeleton_Axe_Red_Spawn::Initialize()
{
	CMonsterState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(6);
}

CMonsterState* CSkeleton_Axe_Red_Spawn::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
		return new CSkeleton_Axe_Red_Idle;

	return NULL;
}
