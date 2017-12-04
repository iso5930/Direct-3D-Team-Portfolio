#include "StdAfx.h"
#include "WitchDoctor_Male_STF_Summon_Charger.h"

CWitchDoctor_Male_STF_Summon_Charger::CWitchDoctor_Male_STF_Summon_Charger(void)
{
	m_eStateType = STATE_TYPE_WITCHDOCTOR_MALE_STF_SUMMON_CHARGER;
}

CWitchDoctor_Male_STF_Summon_Charger::~CWitchDoctor_Male_STF_Summon_Charger(void)
{
}

void CWitchDoctor_Male_STF_Summon_Charger::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(65);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CWitchDoctor_Male_STF_Summon_Charger::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CWitchDoctor_Male_STF_Idle;	
	}
	return NULL;
}
