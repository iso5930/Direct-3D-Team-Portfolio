#include "StdAfx.h"
#include "Triune_Berserker_Attack2.h"

CTriune_Berserker_Attack2::CTriune_Berserker_Attack2(void)
{
	// StateType
	m_eStateType = STATE_TYPE_TRIUNE_BERSERKER_ATTACK2;

	// Mode
	m_iMode = 0;

	// Time
	m_fTime = 0.0f;

	// Effect
	m_pMaceTrail = NULL;
	m_fEffectTime = 0.0f;
	m_iEffect = 0;
}

CTriune_Berserker_Attack2::~CTriune_Berserker_Attack2(void)
{
	if(m_pMaceTrail != NULL)
		m_pMaceTrail->Destroy();
}

void CTriune_Berserker_Attack2::Initialize()
{
	CMonsterState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(3);

	CSoundMgr::GetInstance()->PlaySoundForMonster(_T("Berserker_Attack2.ogg"));
}

CMonsterState* CTriune_Berserker_Attack2::Action()
{
	m_fEffectTime += CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fEffectTime > 0.5f && m_iEffect == 0)
	{
		m_pMaceTrail= new CSkeleton_AxeTrailEffect(NULL, OBJ_TYPE_DYNAMIC, &((CTriune_Berserker*)m_pOwner)->m_WeaponBone.mWorld);
		m_pOwner->GetLayer()->AddObject(m_pMaceTrail, LAYER_TYPE_EFFECT);
		m_pMaceTrail->Initialize();
		m_iEffect = 1;
	}

	if(m_pAnimController->GetTrackPos() > 1.45f && m_iEffect == 1)
	{
		m_pMaceTrail->Destroy();
		m_pMaceTrail = NULL;
		m_iEffect = 2;
	}

	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
		return new CTriune_Berserker_Run(1);

	switch(m_iMode)
	{
	case 0:
		return Mode0();

	case 1:
		return Mode1();
	}

	return NULL;
}

CMonsterState* CTriune_Berserker_Attack2::Mode0()
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

CMonsterState* CTriune_Berserker_Attack2::Mode1()
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
