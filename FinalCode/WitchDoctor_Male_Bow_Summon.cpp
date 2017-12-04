#include "StdAfx.h"
#include "WitchDoctor_Male_Bow_Summon.h"

CWitchDoctor_Male_Bow_Summon::CWitchDoctor_Male_Bow_Summon(void)
{
	m_eStateType = STATE_TYPE_WITCHDOCTOR_MALE_BOW_SUMMON;
}

CWitchDoctor_Male_Bow_Summon::~CWitchDoctor_Male_Bow_Summon(void)
{
}

void CWitchDoctor_Male_Bow_Summon::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(66);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CWitchDoctor_Male_Bow_Summon::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CWitchDoctor_Male_Bow_Idle;	
	}
	return NULL;
}
