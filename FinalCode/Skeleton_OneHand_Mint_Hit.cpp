#include "StdAfx.h"
#include "Skeleton_OneHand_Mint_Hit.h"

CSkeleton_OneHand_Mint_Hit::CSkeleton_OneHand_Mint_Hit(void)
{
	// StateType
	m_eStateType = STATE_TYPE_SKELETON_ONEHAND_MINT_HIT;
}

CSkeleton_OneHand_Mint_Hit::~CSkeleton_OneHand_Mint_Hit(void)
{
}

void CSkeleton_OneHand_Mint_Hit::Initialize()
{
	CMonsterState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(3);
}

CMonsterState* CSkeleton_OneHand_Mint_Hit::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
		return new CSkeleton_OneHand_Mint_Run(2);

	return NULL;
}