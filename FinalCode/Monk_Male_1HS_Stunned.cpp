#include "StdAfx.h"
#include "Monk_Male_1HS_Stunned.h"

CMonk_Male_1HS_Stunned::CMonk_Male_1HS_Stunned(void)
{
	m_eStateType = STATE_TYPE_MONK_MALE_1HS_STUNNED;
}

CMonk_Male_1HS_Stunned::~CMonk_Male_1HS_Stunned(void)
{
}

void CMonk_Male_1HS_Stunned::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(26);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CMonk_Male_1HS_Stunned::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CMonk_Male_1HS_Idle;	
	}
	return NULL;
}
