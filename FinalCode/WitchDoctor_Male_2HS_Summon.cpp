#include "StdAfx.h"
#include "WitchDoctor_Male_2HS_Summon.h"

CWitchDoctor_Male_2HS_Summon::CWitchDoctor_Male_2HS_Summon(void)
{
	m_eStateType = STATE_TYPE_WITCHDOCTOR_MALE_2HS_SUMMON;
}

CWitchDoctor_Male_2HS_Summon::~CWitchDoctor_Male_2HS_Summon(void)
{
}

void CWitchDoctor_Male_2HS_Summon::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(66);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CWitchDoctor_Male_2HS_Summon::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CWitchDoctor_Male_2HS_Idle;	
	}
	return NULL;
}
