#include "StdAfx.h"
#include "Monk_Male_DW_SF_WaveofLight.h"

CMonk_Male_DW_SF_WaveofLight::CMonk_Male_DW_SF_WaveofLight(void)
{
	m_eStateType = STATE_TYPE_MONK_MALE_DW_SF_WAVEOFLIGHT;
}

CMonk_Male_DW_SF_WaveofLight::~CMonk_Male_DW_SF_WaveofLight(void)
{
}

void CMonk_Male_DW_SF_WaveofLight::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(53);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CMonk_Male_DW_SF_WaveofLight::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CMonk_Male_DW_SF_Idle;	
	}
	return NULL;
}
