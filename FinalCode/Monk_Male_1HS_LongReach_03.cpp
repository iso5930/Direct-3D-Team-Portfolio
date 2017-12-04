#include "StdAfx.h"
#include "Monk_Male_1HS_LongReach_03.h"

CMonk_Male_1HS_LongReach_03::CMonk_Male_1HS_LongReach_03(void)
{
	m_eStateType = STATE_TYPE_MONK_MALE_1HS_LONGREACH_03;
}

CMonk_Male_1HS_LongReach_03::~CMonk_Male_1HS_LongReach_03(void)
{
}

void CMonk_Male_1HS_LongReach_03::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(60);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CMonk_Male_1HS_LongReach_03::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.2 <= m_pAnimController->GetTrackPos())
	{
		return new CMonk_Male_1HS_Idle;	
	}
	return NULL;
}
