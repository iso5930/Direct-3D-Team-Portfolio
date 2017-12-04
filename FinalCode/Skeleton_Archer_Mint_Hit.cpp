#include "StdAfx.h"
#include "Skeleton_Archer_Mint_Hit.h"

CSkeleton_Archer_Mint_Hit::CSkeleton_Archer_Mint_Hit(void)
{
	// StateType
	m_eStateType = STATE_TYPE_SKELETON_ARCHER_MINT_HIT;
}

CSkeleton_Archer_Mint_Hit::~CSkeleton_Archer_Mint_Hit(void)
{
}

void CSkeleton_Archer_Mint_Hit::Initialize()
{
	CMonsterState::Initialize();
	
	// SetAnimation
	m_pOwner->SetAnimation(4);
}

CMonsterState* CSkeleton_Archer_Mint_Hit::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
		return new CSkeleton_Archer_Mint_Run(2);

	return NULL;
}