#include "StdAfx.h"
#include "Triune_Vessel_Activating.h"

CTriune_Vessel_Activating::CTriune_Vessel_Activating(void)
{
	// StateType
	m_eStateType = STATE_TYPE_TRIUNE_VESSEL_ACTIVATING;

	// Time
	m_fActivationTime = 0.0f;

	// Count
	m_iActivationCount = 0;
}

CTriune_Vessel_Activating::~CTriune_Vessel_Activating(void)
{
}

void CTriune_Vessel_Activating::Initialize()
{
	CMonsterState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(2);

	CSoundMgr::GetInstance()->PlaySoundForMonster(_T("Vessel_Activating.ogg"));
}

CMonsterState* CTriune_Vessel_Activating::Action()
{
	m_fActivationTime += CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fActivationTime > 1.65)
	{
		++m_iActivationCount;
		m_fActivationTime = 0.0f;
	}

	if(m_iActivationCount == 5)
		return new CTriune_Vessel_Activation;

	return NULL;
}
