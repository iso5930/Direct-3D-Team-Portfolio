#include "StdAfx.h"
#include "Monk_Male_2HT_Stunned.h"

CMonk_Male_2HT_Stunned::CMonk_Male_2HT_Stunned(void)
{
	m_eStateType = STATE_TYPE_MONK_MALE_2HT_STUNNED;
}

CMonk_Male_2HT_Stunned::~CMonk_Male_2HT_Stunned(void)
{
}

void CMonk_Male_2HT_Stunned::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(25);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CMonk_Male_2HT_Stunned::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CMonk_Male_2HT_Idle;	
	}
	return NULL;
}
