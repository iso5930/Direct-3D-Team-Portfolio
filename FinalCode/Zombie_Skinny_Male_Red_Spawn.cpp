#include "StdAfx.h"
#include "Zombie_Skinny_Male_Red_Spawn.h"

CZombie_Skinny_Male_Red_Spawn::CZombie_Skinny_Male_Red_Spawn(void)
{
	// StateType
	m_eStateType = STATE_TYPE_ZOMBIE_SKINNY_MALE_RED_SPAWN;
}

CZombie_Skinny_Male_Red_Spawn::~CZombie_Skinny_Male_Red_Spawn(void)
{
}

void CZombie_Skinny_Male_Red_Spawn::Initialize()
{
	CMonsterState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(8);
}

CMonsterState* CZombie_Skinny_Male_Red_Spawn::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
		return new CZombie_Skinny_Male_Red_Idle(0);

	return NULL;
}
