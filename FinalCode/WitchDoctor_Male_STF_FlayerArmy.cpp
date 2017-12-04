#include "StdAfx.h"
#include "WitchDoctor_Male_STF_FlayerArmy.h"

CWitchDoctor_Male_STF_FlayerArmy::CWitchDoctor_Male_STF_FlayerArmy(void)
{
	m_eStateType = STATE_TYPE_WITCHDOCTOR_MALE_STF_FLAYERARMY;
}

CWitchDoctor_Male_STF_FlayerArmy::~CWitchDoctor_Male_STF_FlayerArmy(void)
{
}

void CWitchDoctor_Male_STF_FlayerArmy::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(67);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CWitchDoctor_Male_STF_FlayerArmy::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CWitchDoctor_Male_STF_Idle;	
	}
	return NULL;
}
