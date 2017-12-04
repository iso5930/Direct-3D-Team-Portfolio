#include "StdAfx.h"
#include "Ghoul_Hit.h"

CGhoul_Hit::CGhoul_Hit(void)
{
	// StateType
	m_eStateType = STATE_TYPE_GHOUL_HIT;
}

CGhoul_Hit::~CGhoul_Hit(void)
{
}

void CGhoul_Hit::Initialize()
{
	CMonsterState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(4);

	CSoundMgr::GetInstance()->PlaySoundForMonster(_T("Ghoul_Hit.ogg"));
}

CMonsterState* CGhoul_Hit::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
		return new CGhoul_Run(2);

	return NULL;
}