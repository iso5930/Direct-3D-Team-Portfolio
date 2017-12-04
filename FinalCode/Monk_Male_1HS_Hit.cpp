#include "StdAfx.h"
#include "Monk_Male_1HS_Hit.h"

CMonk_Male_1HS_Hit::CMonk_Male_1HS_Hit(void)
{
	m_eStateType = STATE_TYPE_MONK_MALE_1HS_HIT;
}

CMonk_Male_1HS_Hit::~CMonk_Male_1HS_Hit(void)
{
}

void CMonk_Male_1HS_Hit::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(34);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CMonk_Male_1HS_Hit::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CMonk_Male_1HS_Idle;	
	}
	return NULL;
}
