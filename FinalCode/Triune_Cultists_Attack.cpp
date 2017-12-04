#include "StdAfx.h"
#include "Triune_Cultists_Attack.h"

CTriune_Cultists_Attack::CTriune_Cultists_Attack(void)
{
	// StateType
	m_eStateType = STATE_TYPE_TRIUNE_CULTISTS_ATTACK;

	// Mode
	m_iMode = 0;

	// Time
	m_fTime = 0.0f;
}

CTriune_Cultists_Attack::~CTriune_Cultists_Attack(void)
{
}


void CTriune_Cultists_Attack::Initialize()
{
	CMonsterState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(3);

	CSoundMgr::GetInstance()->PlaySoundForMonster(_T("Cultist_Attack.ogg"));
}

CMonsterState* CTriune_Cultists_Attack::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
		return new CTriune_Cultists_Run(0);

	switch(m_iMode)
	{
	case 0:
		return Mode0();

	case 1:
		return Mode1();
	}

	return NULL;
}

CMonsterState* CTriune_Cultists_Attack::Mode0()
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

CMonsterState* CTriune_Cultists_Attack::Mode1()
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
