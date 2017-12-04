#include "StdAfx.h"
#include "Monk_Male_DW_SS_Knockback_End.h"

CMonk_Male_DW_SS_Knockback_End::CMonk_Male_DW_SS_Knockback_End(void)
{
	m_eStateType = STATE_TYPE_MONK_MALE_DW_SS_KNOCKBACK_END;
}

CMonk_Male_DW_SS_Knockback_End::~CMonk_Male_DW_SS_Knockback_End(void)
{
}

void CMonk_Male_DW_SS_Knockback_End::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(7);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CMonk_Male_DW_SS_Knockback_End::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CMonk_Male_DW_SS_Idle;	
	}
	return NULL;
}
