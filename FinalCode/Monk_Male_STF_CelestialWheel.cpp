#include "StdAfx.h"
#include "Monk_Male_STF_CelestialWheel.h"

CMonk_Male_STF_CelestialWheel::CMonk_Male_STF_CelestialWheel(void)
{
	m_eStateType = STATE_TYPE_MONK_MALE_STF_CELESTIALWHEEL;
}

CMonk_Male_STF_CelestialWheel::~CMonk_Male_STF_CelestialWheel(void)
{
}

void CMonk_Male_STF_CelestialWheel::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(53);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CMonk_Male_STF_CelestialWheel::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CMonk_Male_STF_Idle;	
	}
	return NULL;
}
