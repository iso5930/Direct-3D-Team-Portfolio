#include "StdAfx.h"
#include "WitchDoctor_Male_STF_Summon.h"

CWitchDoctor_Male_STF_Summon::CWitchDoctor_Male_STF_Summon(void)
{
	m_eStateType = STATE_TYPE_WITCHDOCTOR_MALE_STF_SUMMON;
}

CWitchDoctor_Male_STF_Summon::~CWitchDoctor_Male_STF_Summon(void)
{
}

void CWitchDoctor_Male_STF_Summon::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(66);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CWitchDoctor_Male_STF_Summon::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CWitchDoctor_Male_STF_Idle;	
	}
	return NULL;
}
