#include "StdAfx.h"
#include "Skeleton_Summoner_Red_Hit.h"

CSkeleton_Summoner_Red_Hit::CSkeleton_Summoner_Red_Hit(void)
{
	// StateType
	m_eStateType = STATE_TYPE_SKELETON_SUMMONER_RED_HIT;
}

CSkeleton_Summoner_Red_Hit::~CSkeleton_Summoner_Red_Hit(void)
{
}

void CSkeleton_Summoner_Red_Hit::Initialize()
{
	CMonsterState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(4);
}

CMonsterState* CSkeleton_Summoner_Red_Hit::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
		return new CSkeleton_Summoner_Red_Walk(3);

	return NULL;
}
