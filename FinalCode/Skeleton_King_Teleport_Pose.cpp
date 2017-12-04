#include "StdAfx.h"
#include "Skeleton_King_Teleport_Pose.h"

CSkeleton_King_Teleport_Pose::CSkeleton_King_Teleport_Pose(void)
{
	m_eStateType = STATE_TYPE_SKELETON_KING_TELEPORT_POSE;
}

CSkeleton_King_Teleport_Pose::~CSkeleton_King_Teleport_Pose(void)
{
}

void CSkeleton_King_Teleport_Pose::Initialize()
{
	CMonsterState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(15);
}

CMonsterState* CSkeleton_King_Teleport_Pose::Action()
{
	return NULL;
}
