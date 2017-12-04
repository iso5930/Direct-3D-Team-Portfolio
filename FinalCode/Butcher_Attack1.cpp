#include "StdAfx.h"
#include "Butcher_Attack1.h"

CButcher_Attack1::CButcher_Attack1(void)
{
	// StateType
	m_eStateType = STATE_TYPE_BUTCHER_ATTACK1;

	// Mode
	m_iMode = 0;
	
	// Time
	m_fTime = 0.0f;

	// Effect
	m_iEffect = 0;
}

CButcher_Attack1::~CButcher_Attack1(void)
{
}

void CButcher_Attack1::Initialize()
{
	CMonsterState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(8);
}

CMonsterState* CButcher_Attack1::Action()
{
	if(m_pAnimController->GetTrackPos() > 1.6f && m_iEffect == 0)
	{
		
		m_pAxeTrail = new CButcher_AxeTrail(NULL, OBJ_TYPE_DYNAMIC, &((CButcher*)m_pOwner)->m_RightWeaponBone.mWorld);
		m_pOwner->GetLayer()->AddObject(m_pAxeTrail, LAYER_TYPE_EFFECT);
		m_pAxeTrail->Initialize();
		m_iEffect = 1;
	}

	if(m_pAnimController->GetTrackPos() > 2.178f && m_iEffect == 1)
	{
		m_pAxeTrail->Destroy();
		m_pAxeTrail = NULL;
		m_iEffect = 2;
	}

	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
		return new CButcher_Idle;

	switch(m_iMode)
	{
	case 0:
		return Mode0();

	case 1:
		return Mode1();
	}

	return NULL;
}

CMonsterState* CButcher_Attack1::Mode0()
{
	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();
	if(m_fTime > 1.65f)
	{
		m_pOwner->CreateAttack();

		m_fTime = 0.0f;
		++m_iMode;
	}
	return NULL;
}

CMonsterState* CButcher_Attack1::Mode1()
{	
	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();
	if(m_fTime > 1.2f)
	{
		m_pOwner->RemoveAttack();

		m_fTime = 0.0f;
		++m_iMode;
	}
	return NULL;
}
