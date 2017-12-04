#include "StdAfx.h"
#include "Skeleton_Archer_Brown_Hit.h"

CSkeleton_Archer_Brown_Hit::CSkeleton_Archer_Brown_Hit(void)
{
	// StateType
	m_eStateType = STATE_TYPE_SKELETON_ARCHER_BROWN_HIT;
}

CSkeleton_Archer_Brown_Hit::~CSkeleton_Archer_Brown_Hit(void)
{
}

void CSkeleton_Archer_Brown_Hit::Initialize()
{
	CMonsterState::Initialize();
	
	// SetAnimation
	m_pOwner->SetAnimation(4);
}

CMonsterState* CSkeleton_Archer_Brown_Hit::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
		return new CSkeleton_Archer_Brown_Run(2);

	return NULL;
}