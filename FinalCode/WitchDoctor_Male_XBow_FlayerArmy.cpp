#include "StdAfx.h"
#include "WitchDoctor_Male_XBow_FlayerArmy.h"

CWitchDoctor_Male_XBow_FlayerArmy::CWitchDoctor_Male_XBow_FlayerArmy(void)
{
	m_eStateType = STATE_TYPE_WITCHDOCTOR_MALE_XBOW_FLAYERARMY;
}

CWitchDoctor_Male_XBow_FlayerArmy::~CWitchDoctor_Male_XBow_FlayerArmy(void)
{
}

void CWitchDoctor_Male_XBow_FlayerArmy::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(67);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CWitchDoctor_Male_XBow_FlayerArmy::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CWitchDoctor_Male_XBow_Idle;	
	}
	return NULL;
}
