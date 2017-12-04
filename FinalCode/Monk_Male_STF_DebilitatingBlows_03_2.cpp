#include "StdAfx.h"
#include "Monk_Male_STF_DebilitatingBlows_03_2.h"

CMonk_Male_STF_DebilitatingBlows_03_2::CMonk_Male_STF_DebilitatingBlows_03_2(void)
{
	m_eStateType = STATE_TYPE_MONK_MALE_STF_DEBILITATINGBLOWS_03_2;
}

CMonk_Male_STF_DebilitatingBlows_03_2::~CMonk_Male_STF_DebilitatingBlows_03_2(void)
{
}

void CMonk_Male_STF_DebilitatingBlows_03_2::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(67);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CMonk_Male_STF_DebilitatingBlows_03_2::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CMonk_Male_STF_Idle;	
	}
	return NULL;
}
