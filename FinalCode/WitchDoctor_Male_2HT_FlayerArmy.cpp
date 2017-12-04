#include "StdAfx.h"
#include "WitchDoctor_Male_2HT_FlayerArmy.h"

CWitchDoctor_Male_2HT_FlayerArmy::CWitchDoctor_Male_2HT_FlayerArmy(void)
{
	m_eStateType = STATE_TYPE_WITCHDOCTOR_MALE_2HT_FLAYERARMY;
}

CWitchDoctor_Male_2HT_FlayerArmy::~CWitchDoctor_Male_2HT_FlayerArmy(void)
{
}

void CWitchDoctor_Male_2HT_FlayerArmy::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(67);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CWitchDoctor_Male_2HT_FlayerArmy::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CWitchDoctor_Male_2HT_Idle;	
	}
	return NULL;
}
