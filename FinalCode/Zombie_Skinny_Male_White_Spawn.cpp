#include "StdAfx.h"
#include "Zombie_Skinny_Male_White_Spawn.h"

CZombie_Skinny_Male_White_Spawn::CZombie_Skinny_Male_White_Spawn(void)
{
}

CZombie_Skinny_Male_White_Spawn::~CZombie_Skinny_Male_White_Spawn(void)
{
}

void CZombie_Skinny_Male_White_Spawn::Initialize()
{
	CMonsterState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(8);
}

CMonsterState* CZombie_Skinny_Male_White_Spawn::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
		return new CZombie_Skinny_Male_White_Idle(0);

	return NULL;
}
