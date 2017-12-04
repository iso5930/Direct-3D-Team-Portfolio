#include "StdAfx.h"
#include "Monk_Male_DW_FF_CelestialWheel.h"

CMonk_Male_DW_FF_CelestialWheel::CMonk_Male_DW_FF_CelestialWheel(void)
{
	m_eStateType = STATE_TYPE_MONK_MALE_DW_FF_CELESTIALWHEEL;
}

CMonk_Male_DW_FF_CelestialWheel::~CMonk_Male_DW_FF_CelestialWheel(void)
{
}

void CMonk_Male_DW_FF_CelestialWheel::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(53);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CMonk_Male_DW_FF_CelestialWheel::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CMonk_Male_DW_FF_Idle;	
	}
	return NULL;
}
