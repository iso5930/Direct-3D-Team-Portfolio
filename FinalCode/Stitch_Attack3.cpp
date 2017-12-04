#include "StdAfx.h"
#include "Stitch_Attack3.h"

CStitch_Attack3::CStitch_Attack3(void)
{
	// StateType
	m_eStateType = STATE_TYPE_STITCH_ATTACK3;

	// Mode
	m_iMode = 0;

	// Time
	m_fTime = 0.0f;
}

CStitch_Attack3::~CStitch_Attack3(void)
{
}

void CStitch_Attack3::Initialize()
{
	CMonsterState::Initialize();

	//SetAnimation
	m_pOwner->SetAnimation(5);

	CSoundMgr::GetInstance()->PlaySoundForMonster(_T("Stitch_Attack3.ogg"));
}

CMonsterState* CStitch_Attack3::Action()
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

CMonsterState* CStitch_Attack3::Mode0()
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

CMonsterState* CStitch_Attack3::Mode1()
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