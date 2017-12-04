#include "StdAfx.h"
#include "Monk_Male_STF_Hit.h"

CMonk_Male_STF_Hit::CMonk_Male_STF_Hit(void)
{
	m_eStateType = STATE_TYPE_MONK_MALE_STF_HIT;
}

CMonk_Male_STF_Hit::~CMonk_Male_STF_Hit(void)
{
}

void CMonk_Male_STF_Hit::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(31);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CMonk_Male_STF_Hit::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CMonk_Male_STF_Idle;	
	}
	return NULL;
}
