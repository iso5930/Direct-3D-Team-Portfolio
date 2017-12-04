#include "StdAfx.h"
#include "Monk_Male_2HT_Hit.h"

CMonk_Male_2HT_Hit::CMonk_Male_2HT_Hit(void)
{
	m_eStateType = STATE_TYPE_MONK_MALE_2HT_HIT;
}

CMonk_Male_2HT_Hit::~CMonk_Male_2HT_Hit(void)
{
}

void CMonk_Male_2HT_Hit::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(32);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CMonk_Male_2HT_Hit::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CMonk_Male_2HT_Idle;	
	}
	return NULL;
}
