#include "StdAfx.h"
#include "Monk_Male_1HS_WaveofLight.h"

CMonk_Male_1HS_WaveofLight::CMonk_Male_1HS_WaveofLight(void)
{
	m_eStateType = STATE_TYPE_MONK_MALE_1HS_WAVEOFLIGHT;
}

CMonk_Male_1HS_WaveofLight::~CMonk_Male_1HS_WaveofLight(void)
{
}

void CMonk_Male_1HS_WaveofLight::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(53);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CMonk_Male_1HS_WaveofLight::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CMonk_Male_1HS_Idle;	
	}
	return NULL;
}
