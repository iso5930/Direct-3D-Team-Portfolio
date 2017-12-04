#include "StdAfx.h"
#include "WitchDoctor_Male_1HT_Summon.h"

CWitchDoctor_Male_1HT_Summon::CWitchDoctor_Male_1HT_Summon(void)
{
	m_eStateType = STATE_TYPE_WITCHDOCTOR_MALE_1HT_SUMMON;
}

CWitchDoctor_Male_1HT_Summon::~CWitchDoctor_Male_1HT_Summon(void)
{
}

void CWitchDoctor_Male_1HT_Summon::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(66);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CWitchDoctor_Male_1HT_Summon::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CWitchDoctor_Male_1HT_Idle;	
	}
	return NULL;
}
