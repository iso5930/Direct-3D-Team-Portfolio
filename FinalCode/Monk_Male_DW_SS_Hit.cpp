#include "StdAfx.h"
#include "Monk_Male_DW_SS_Hit.h"

CMonk_Male_DW_SS_Hit::CMonk_Male_DW_SS_Hit(void)
{
	m_eStateType = STATE_TYPE_MONK_MALE_DW_SS_HIT;
}

CMonk_Male_DW_SS_Hit::~CMonk_Male_DW_SS_Hit(void)
{
}

void CMonk_Male_DW_SS_Hit::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(28);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CMonk_Male_DW_SS_Hit::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CMonk_Male_DW_SS_Idle;	
	}
	return NULL;
}
