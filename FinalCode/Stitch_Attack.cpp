#include "StdAfx.h"
#include "Stitch_Attack.h"

CStitch_Attack::CStitch_Attack(void)
{
	// StateType
	m_eStateType = STATE_TYPE_STITCH_ATTACK;

	// Mode 
	m_iMode = 0;

	// Time
	m_fTime = 0.0f;

}

CStitch_Attack::~CStitch_Attack(void)
{
}

void CStitch_Attack::Initialize()
{
	CMonsterState::Initialize();

	// SetAnimaiton
	m_pOwner->SetAnimation(3);

	CSoundMgr::GetInstance()->PlaySoundForMonster(_T("Stitch_Attack.ogg"));
}

CMonsterState* CStitch_Attack::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
		return new CStitch_Run(0);

	switch(m_iMode)
	{
	case 0:
		return Mode0();

	case 1:
		return Mode1();
	}

	return NULL;
}

CMonsterState* CStitch_Attack::Mode0()
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

CMonsterState* CStitch_Attack::Mode1()
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

