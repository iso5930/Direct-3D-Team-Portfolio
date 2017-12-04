#include "StdAfx.h"
#include "Monk_Male_DW_SF_Stunned.h"

CMonk_Male_DW_SF_Stunned::CMonk_Male_DW_SF_Stunned(void)
{
	m_eStateType = STATE_TYPE_MONK_MALE_DW_SF_STUNNED;
}

CMonk_Male_DW_SF_Stunned::~CMonk_Male_DW_SF_Stunned(void)
{
}

void CMonk_Male_DW_SF_Stunned::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(22);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CMonk_Male_DW_SF_Stunned::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CMonk_Male_DW_SF_Idle;	
	}
	return NULL;
}
