#include "StdAfx.h"
#include "Zombie_Skinny_Male_Red_Attack4.h"

CZombie_Skinny_Male_Red_Attack4::CZombie_Skinny_Male_Red_Attack4(void)
{
	// StateType
	m_eStateType = STATE_TYPE_ZOMBIE_SKINNY_MALE_RED_ATTACK4;

	// Mode
	m_iMode = 0;

	// Time
	m_fTime = 0.f;

}

CZombie_Skinny_Male_Red_Attack4::~CZombie_Skinny_Male_Red_Attack4(void)
{
}


void CZombie_Skinny_Male_Red_Attack4::Initialize()
{
	CMonsterState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(5);

	CSoundMgr::GetInstance()->PlaySoundForMonster(_T("Zombie_Skinny_Male_Attack4.ogg"));
}

CMonsterState* CZombie_Skinny_Male_Red_Attack4::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
		return new CZombie_Skinny_Male_Red_Walk1(1);

	switch(m_iMode)
	{
	case 0:
		return Mode0();

	case 1:
		return Mode1();
	}
	return NULL;
}

CMonsterState* CZombie_Skinny_Male_Red_Attack4::Mode0()
{
	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();
	if(m_fTime > 0.0f)
	{
		m_pOwner->CreateAttack();

		m_fTime = 0.0f;
		++m_iMode;
	}

	return NULL;
}

CMonsterState* CZombie_Skinny_Male_Red_Attack4::Mode1()
{
	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();
	if(m_fTime > 1.f)
	{
		m_pOwner->RemoveAttack();

		m_fTime = 0.0f;
		++m_iMode;
	}

	return NULL;
}
