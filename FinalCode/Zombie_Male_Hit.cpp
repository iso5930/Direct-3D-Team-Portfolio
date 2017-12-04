#include "StdAfx.h"
#include "Zombie_Male_Hit.h"

CZombie_Male_Hit::CZombie_Male_Hit(void)
{
	// StateType
	m_eStateType = STATE_TYPE_ZOMBIE_MALE_HIT;
}

CZombie_Male_Hit::~CZombie_Male_Hit(void)
{
}

void CZombie_Male_Hit::Initialize()
{
	CMonsterState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(3);

	CSoundMgr::GetInstance()->PlaySoundForMonster(_T("Zombie_Male_Attack.ogg"));
}

CMonsterState* CZombie_Male_Hit::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
		return new CZombie_Male_Walk(3);

	return NULL;
}