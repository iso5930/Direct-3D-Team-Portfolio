#include "StdAfx.h"
#include "Skeleton_OneHand_Blue_Hit.h"

CSkeleton_OneHand_Blue_Hit::CSkeleton_OneHand_Blue_Hit(void)
{
	// StateType
	m_eStateType = STATE_TYPE_SKELETON_ONEHAND_BLUE_HIT;
}

CSkeleton_OneHand_Blue_Hit::~CSkeleton_OneHand_Blue_Hit(void)
{
}

void CSkeleton_OneHand_Blue_Hit::Initialize()
{
	CMonsterState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(3);
}

CMonsterState* CSkeleton_OneHand_Blue_Hit::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
		return new CSkeleton_OneHand_Blue_Run(2);
	return NULL;
}