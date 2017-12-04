#include "StdAfx.h"
#include "Stitch_Attack2.h"

CStitch_Attack2::CStitch_Attack2(void)
{
	// StateType
	m_eStateType = STATE_TYPE_STITCH_ATTACK2;

	// Mode
	m_iMode = 0;

	// Time
	m_fTime = 0.0f;

	m_bEffect = false;

	m_pSpike = NULL;
}

CStitch_Attack2::~CStitch_Attack2(void)
{
}

void CStitch_Attack2::Initialize()
{
	CMonsterState::Initialize();

	//SetAnimation
	m_pOwner->SetAnimation(4);

	CSoundMgr::GetInstance()->PlaySoundForMonster(_T("Stitch_Attack2.ogg"));
}

CMonsterState* CStitch_Attack2::Action()
{
	if(!m_bEffect)
	{
		m_pSpike = new CStitch_Spike(NULL, OBJ_TYPE_DYNAMIC, m_pOwner, &((CStitch*)m_pOwner)->m_SpikeABone);
		m_pOwner->GetLayer()->AddObject(m_pSpike, LAYER_TYPE_EFFECT);
		m_pSpike->Initialize();

		m_pSpike = new CStitch_Spike(NULL, OBJ_TYPE_DYNAMIC, m_pOwner, &((CStitch*)m_pOwner)->m_SpikeBBone);
		m_pOwner->GetLayer()->AddObject(m_pSpike, LAYER_TYPE_EFFECT);
		m_pSpike->Initialize();

		m_pSpike = new CStitch_Spike(NULL, OBJ_TYPE_DYNAMIC, m_pOwner, &((CStitch*)m_pOwner)->m_SpikeCBone);
		m_pOwner->GetLayer()->AddObject(m_pSpike, LAYER_TYPE_EFFECT);
		m_pSpike->Initialize();

		m_pSpike = new CStitch_Spike(NULL, OBJ_TYPE_DYNAMIC, m_pOwner, &((CStitch*)m_pOwner)->m_SpikeDBone);
		m_pOwner->GetLayer()->AddObject(m_pSpike, LAYER_TYPE_EFFECT);
		m_pSpike->Initialize();

		m_pSpike = new CStitch_Spike(NULL, OBJ_TYPE_DYNAMIC, m_pOwner, &((CStitch*)m_pOwner)->m_SpikeEBone);
		m_pOwner->GetLayer()->AddObject(m_pSpike, LAYER_TYPE_EFFECT);
		m_pSpike->Initialize();

		m_pSpike = new CStitch_Spike(NULL, OBJ_TYPE_DYNAMIC, m_pOwner, &((CStitch*)m_pOwner)->m_SpikeFBone);
		m_pOwner->GetLayer()->AddObject(m_pSpike, LAYER_TYPE_EFFECT);
		m_pSpike->Initialize();

		m_pSpike = new CStitch_Spike(NULL, OBJ_TYPE_DYNAMIC, m_pOwner, &((CStitch*)m_pOwner)->m_SpikeGBone);
		m_pOwner->GetLayer()->AddObject(m_pSpike, LAYER_TYPE_EFFECT);
		m_pSpike->Initialize();

		m_pSpike = new CStitch_Spike(NULL, OBJ_TYPE_DYNAMIC, m_pOwner, &((CStitch*)m_pOwner)->m_SpikeHBone);
		m_pOwner->GetLayer()->AddObject(m_pSpike, LAYER_TYPE_EFFECT);
		m_pSpike->Initialize();

		m_pSpike = new CStitch_Spike(NULL, OBJ_TYPE_DYNAMIC, m_pOwner, &((CStitch*)m_pOwner)->m_SpikeIBone);
		m_pOwner->GetLayer()->AddObject(m_pSpike, LAYER_TYPE_EFFECT);
		m_pSpike->Initialize();

		m_pSpike = new CStitch_Spike(NULL, OBJ_TYPE_DYNAMIC, m_pOwner, &((CStitch*)m_pOwner)->m_SpikeJBone);
		m_pOwner->GetLayer()->AddObject(m_pSpike, LAYER_TYPE_EFFECT);
		m_pSpike->Initialize();

		m_pSpike = new CStitch_Spike(NULL, OBJ_TYPE_DYNAMIC, m_pOwner, &((CStitch*)m_pOwner)->m_SpikeKBone);
		m_pOwner->GetLayer()->AddObject(m_pSpike, LAYER_TYPE_EFFECT);
		m_pSpike->Initialize();

		m_bEffect = true;
	}

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

CMonsterState* CStitch_Attack2::Mode0()
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

CMonsterState* CStitch_Attack2::Mode1()
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