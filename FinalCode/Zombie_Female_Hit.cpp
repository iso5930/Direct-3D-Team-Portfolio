#include "StdAfx.h"
#include "Zombie_Female_Hit.h"

CZombie_Female_Hit::CZombie_Female_Hit()
{
	// StateType
	m_eStateType = STATE_TYPE_ZOMBIE_FEMALE_HIT;
}

CZombie_Female_Hit::~CZombie_Female_Hit()
{
}

void CZombie_Female_Hit::Initialize()
{
	CMonsterState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(6);

	CSoundMgr::GetInstance()->PlaySoundForMonster(_T("Zombie_Female_Hit.ogg"));
}

CMonsterState* CZombie_Female_Hit::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
		return new CZombie_Female_Walk(3);

	return NULL;
}