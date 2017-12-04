#include "StdAfx.h"
#include "Skeleton_Shield_Blue_Hit.h"

CSkeleton_Shield_Blue_Hit::CSkeleton_Shield_Blue_Hit(void)
{
	// StateType
	m_eStateType = STATE_TYPE_SKELETON_SHIELD_BLUE_HIT;
}

CSkeleton_Shield_Blue_Hit::~CSkeleton_Shield_Blue_Hit(void)
{
}

void CSkeleton_Shield_Blue_Hit::Initialize()
{
	CMonsterState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(3);
}

CMonsterState* CSkeleton_Shield_Blue_Hit::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
		return new CSkeleton_Shield_Blue_Walk(2);

	return NULL;
}