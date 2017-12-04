#include "StdAfx.h"
#include "Zombie_Skinny_Male_Red_Hit.h"

CZombie_Skinny_Male_Red_Hit::CZombie_Skinny_Male_Red_Hit(void)
{
	// StateType
	m_eStateType = STATE_TYPE_ZOMBIE_SKINNY_MALE_RED_HIT;
}

CZombie_Skinny_Male_Red_Hit::~CZombie_Skinny_Male_Red_Hit(void)
{
}


void CZombie_Skinny_Male_Red_Hit::Initialize()
{
	CMonsterState::Initialize();

	// SetAnimaiton
	m_pOwner->SetAnimation(6);

	CSoundMgr::GetInstance()->PlaySoundForMonster(_T("Zombie_Skinny_Male_Hit.ogg"));
}

CMonsterState* CZombie_Skinny_Male_Red_Hit::Action()
{	
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
		return new CZombie_Skinny_Male_Red_Walk1(2);

	return NULL;
}
