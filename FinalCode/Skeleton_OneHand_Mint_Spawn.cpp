#include "StdAfx.h"
#include "Skeleton_OneHand_Mint_Spawn.h"

CSkeleton_OneHand_Mint_Spawn::CSkeleton_OneHand_Mint_Spawn(void)
{
	// StateType
	m_eStateType = STATE_TYPE_SKELETON_ONEHAND_MINT_SPAWN;
}

CSkeleton_OneHand_Mint_Spawn::~CSkeleton_OneHand_Mint_Spawn(void)
{
}

void CSkeleton_OneHand_Mint_Spawn::Initialize()
{
	CMonsterState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(5);
}

CMonsterState* CSkeleton_OneHand_Mint_Spawn::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
		return new CSkeleton_OneHand_Mint_Idle;

	return NULL;
}
