#include "StdAfx.h"
#include "Monk_Male_DW_SF_LashingTail.h"

CMonk_Male_DW_SF_LashingTail::CMonk_Male_DW_SF_LashingTail(void)
{
	m_eStateType = STATE_TYPE_MONK_MALE_DW_SF_LASHINGTAIL;
}

CMonk_Male_DW_SF_LashingTail::~CMonk_Male_DW_SF_LashingTail(void)
{
}

void CMonk_Male_DW_SF_LashingTail::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(55);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CMonk_Male_DW_SF_LashingTail::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CMonk_Male_DW_SF_Idle;	
	}
	return NULL;
}
