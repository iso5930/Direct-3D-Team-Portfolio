#include "StdAfx.h"
#include "Skeleton_Axe_Blue_Attack2.h"

CSkeleton_Axe_Blue_Attack2::CSkeleton_Axe_Blue_Attack2(void)
{
	// StateType
	m_eStateType = STATE_TYPE_SKELETON_AXE_BLUE_ATTACK2;

	// Mode
	m_iMode = 0;

	// Time
	m_fTime = 0.0f;
}

CSkeleton_Axe_Blue_Attack2::~CSkeleton_Axe_Blue_Attack2(void)
{
}

void CSkeleton_Axe_Blue_Attack2::Initialize()
{
	CMonsterState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(3);

	CSoundMgr::GetInstance()->PlaySoundForMonsterSkill(_T("Skeleton_Axe_Attack2.ogg"));
}

CMonsterState* CSkeleton_Axe_Blue_Attack2::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
		return new CSkeleton_Axe_Blue_Run(1);

	switch(m_iMode)
	{
	case 0:
		return Mode0();

	case 1:
		return Mode1();
	}

	return NULL;
}

CMonsterState* CSkeleton_Axe_Blue_Attack2::Mode0()
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

CMonsterState* CSkeleton_Axe_Blue_Attack2::Mode1()
{
	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();
	if(m_fTime > 1.0f)
	{
		m_pOwner->RemoveAttack();

		m_fTime = 0.0f;
		++m_iMode;
	}
	return NULL;
}