#include "StdAfx.h"
#include "Monk_Male_1HT_DebilitatingBlows_03_1.h"

CMonk_Male_1HT_DebilitatingBlows_03_1::CMonk_Male_1HT_DebilitatingBlows_03_1(void)
{
	m_eStateType = STATE_TYPE_MONK_MALE_1HT_DEBILITATINGBLOWS_03_1;
}

CMonk_Male_1HT_DebilitatingBlows_03_1::~CMonk_Male_1HT_DebilitatingBlows_03_1(void)
{
}

void CMonk_Male_1HT_DebilitatingBlows_03_1::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(68);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CMonk_Male_1HT_DebilitatingBlows_03_1::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CMonk_Male_1HT_Idle;	
	}
	return NULL;
}
