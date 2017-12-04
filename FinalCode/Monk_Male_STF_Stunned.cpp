#include "StdAfx.h"
#include "Monk_Male_STF_Stunned.h"

CMonk_Male_STF_Stunned::CMonk_Male_STF_Stunned(void)
{
	m_eStateType = STATE_TYPE_MONK_MALE_STF_STUNNED;
}

CMonk_Male_STF_Stunned::~CMonk_Male_STF_Stunned(void)
{
}

void CMonk_Male_STF_Stunned::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(21);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CMonk_Male_STF_Stunned::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CMonk_Male_STF_Idle;	
	}
	return NULL;
}
