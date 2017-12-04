#include "StdAfx.h"
#include "Skeleton_Archer_Red_Hit.h"

CSkeleton_Archer_Red_Hit::CSkeleton_Archer_Red_Hit(void)
{
	// StateType
	m_eStateType = STATE_TYPE_SKELETON_ARCHER_RED_HIT;
}

CSkeleton_Archer_Red_Hit::~CSkeleton_Archer_Red_Hit(void)
{
}

void CSkeleton_Archer_Red_Hit::Initialize()
{
	CMonsterState::Initialize();
	
	// SetAnimation
	m_pOwner->SetAnimation(4);
}

CMonsterState* CSkeleton_Archer_Red_Hit::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
		return new CSkeleton_Archer_Red_Run(2);
	
	return NULL;
}