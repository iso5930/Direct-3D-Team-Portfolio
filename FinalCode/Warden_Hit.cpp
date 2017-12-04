#include "StdAfx.h"
#include "Warden_Hit.h"

CWarden_Hit::CWarden_Hit(void)
{
	// SetType
	m_eStateType = STATE_TYPE_WARDEN_HIT;
}

CWarden_Hit::~CWarden_Hit(void)
{
}

void CWarden_Hit::Initialize()
{
	CMonsterState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(4);
}

CMonsterState* CWarden_Hit::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
		return new CWarden_Run(2);

	return NULL;
}
