#include "StdAfx.h"
#include "Monk_Male_STF_LashingTail.h"

CMonk_Male_STF_LashingTail::CMonk_Male_STF_LashingTail(void)
{
	m_eStateType = STATE_TYPE_MONK_MALE_STF_LASHINGTAIL;
}

CMonk_Male_STF_LashingTail::~CMonk_Male_STF_LashingTail(void)
{
}

void CMonk_Male_STF_LashingTail::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(55);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CMonk_Male_STF_LashingTail::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CMonk_Male_STF_Idle;	
	}
	return NULL;
}
