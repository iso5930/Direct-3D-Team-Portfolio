#include "StdAfx.h"
#include "Skeleton_Shield_Mint_Attack.h"

CSkeleton_Shield_Mint_Attack::CSkeleton_Shield_Mint_Attack(void)
{
	// StateType
	m_eStateType = STATE_TYPE_SKELETON_SHIELD_MINT_ATTACK;

	// Mode
	m_iMode = 0;
	
	// Time
	m_fTime = 0.0f;

	// Effect
	m_pSwordTrail = NULL;
	m_fEffectTime = 0.0f;
	m_iEffect = 0;
}

CSkeleton_Shield_Mint_Attack::~CSkeleton_Shield_Mint_Attack(void)
{
	if(m_pSwordTrail != NULL)
		m_pSwordTrail->Destroy();
}

void CSkeleton_Shield_Mint_Attack::Initialize()
{
	CMonsterState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(2);
}

CMonsterState* CSkeleton_Shield_Mint_Attack::Action()
{
	m_fEffectTime += CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fEffectTime > 0.33f && m_iEffect == 0)
	{
		m_pSwordTrail = new CSkeleton_SwordTrailEffect(NULL, OBJ_TYPE_DYNAMIC, &((CSkeleton_Shield_Mint*)m_pOwner)->m_WeaponBone.mWorld);
		m_pOwner->GetLayer()->AddObject(m_pSwordTrail, LAYER_TYPE_EFFECT);
		m_pSwordTrail->Initialize();
		m_iEffect = 1;
	}

	if(m_fEffectTime > 0.627f && m_iEffect == 1)
	{
		m_pSwordTrail->Destroy();
		m_pSwordTrail = NULL;
		m_iEffect = 2;
	}

	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
		return new CSkeleton_Shield_Mint_Walk(1);

	switch(m_iMode)
	{
	case 0:
		return Mode0();

	case 1:
		return Mode1();
	}

	return NULL;
}

CMonsterState* CSkeleton_Shield_Mint_Attack::Mode0()
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

CMonsterState* CSkeleton_Shield_Mint_Attack::Mode1()
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