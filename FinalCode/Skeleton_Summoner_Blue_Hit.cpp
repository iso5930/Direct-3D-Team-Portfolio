#include "StdAfx.h"
#include "Skeleton_Summoner_Blue_Hit.h"

CSkeleton_Summoner_Blue_Hit::CSkeleton_Summoner_Blue_Hit(void)
{
	// StateType
	m_eStateType = STATE_TYPE_SKELETON_SUMMONER_BLUE_HIT;
}

CSkeleton_Summoner_Blue_Hit::~CSkeleton_Summoner_Blue_Hit(void)
{
}

void CSkeleton_Summoner_Blue_Hit::Initialize()
{
	CMonsterState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(4);
}

CMonsterState* CSkeleton_Summoner_Blue_Hit::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
		return new CSkeleton_Summoner_Blue_Walk(3);

	return NULL;
}
