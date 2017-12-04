#include "StdAfx.h"
#include "Skeleton_King_Taunt.h"

CSkeleton_King_Taunt::CSkeleton_King_Taunt(void)
{
	// StateType
	m_eStateType = STATE_TYPE_SKELETON_KING_TAUNT;
}

CSkeleton_King_Taunt::~CSkeleton_King_Taunt(void)
{
}

void CSkeleton_King_Taunt::Initialize()
{
	CMonsterState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(14);

	CSoundMgr::GetInstance()->PlaySoundForMonster(_T("King_Taunt"));
}

CMonsterState* CSkeleton_King_Taunt::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
		return new CSkeleton_King_Idle(0);

	return NULL;
}