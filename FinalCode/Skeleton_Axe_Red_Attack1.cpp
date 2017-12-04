#include "StdAfx.h"
#include "Skeleton_Axe_Red_Attack1.h"

CSkeleton_Axe_Red_Attack1::CSkeleton_Axe_Red_Attack1(void)
{
	// StateType
	m_eStateType = STATE_TYPE_SKELETON_AXE_RED_ATTACK1;

	// Mode
	m_iMode = 0;

	// Time
	m_fTime = 0.0f;

	// Effect
	m_pAxeTrail = NULL;
	m_fEffectTime = 0.0f;
	m_iEffect = 0;
}

CSkeleton_Axe_Red_Attack1::~CSkeleton_Axe_Red_Attack1(void)
{
	if(m_pAxeTrail != NULL)
		m_pAxeTrail->Destroy();
}

void CSkeleton_Axe_Red_Attack1::Initialize()
{
	CMonsterState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(2);

	CSoundMgr::GetInstance()->PlaySoundForMonsterSkill(_T("Skeleton_Axe_Attack.ogg"));
}

CMonsterState* CSkeleton_Axe_Red_Attack1::Action()
{
	m_fEffectTime += CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fEffectTime > 0.528f && m_iEffect == 0)
	{
		m_pAxeTrail = new CSkeleton_AxeTrailEffect(NULL, OBJ_TYPE_DYNAMIC, &((CSkeleton_Axe_Red*)m_pOwner)->m_WeaponBone.mWorld);
		m_pOwner->GetLayer()->AddObject(m_pAxeTrail, LAYER_TYPE_EFFECT);
		m_pAxeTrail->Initialize();
		m_iEffect = 1;
	}

	if(m_fEffectTime > 0.99f && m_iEffect == 1)
	{
		m_pAxeTrail->Destroy();
		m_pAxeTrail = NULL;
		m_iEffect = 2;
	}

	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
		return new CSkeleton_Axe_Red_Run(1);

	switch(m_iMode)
	{
	case 0:
		return Mode0();

	case 1:
		return Mode1();
	}

	return NULL;
}

CMonsterState* CSkeleton_Axe_Red_Attack1::Mode0()
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

CMonsterState* CSkeleton_Axe_Red_Attack1::Mode1()
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

