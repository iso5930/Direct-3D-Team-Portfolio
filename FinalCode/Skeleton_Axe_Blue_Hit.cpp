#include "StdAfx.h"
#include "Skeleton_Axe_Blue_Hit.h"

CSkeleton_Axe_Blue_Hit::CSkeleton_Axe_Blue_Hit(void)
{
	// StateType
	m_eStateType = STATE_TYPE_SKELETON_AXE_BLUE_HIT;
}

CSkeleton_Axe_Blue_Hit::~CSkeleton_Axe_Blue_Hit(void)
{
}

void CSkeleton_Axe_Blue_Hit::Initialize()
{
	CMonsterState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(4);
}

CMonsterState* CSkeleton_Axe_Blue_Hit::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
		return new CSkeleton_Axe_Blue_Run(2);

	return NULL;
}

