#include "StdAfx.h"
#include "Monk_Male_STF_Lethal_Decoy.h"

CMonk_Male_STF_Lethal_Decoy::CMonk_Male_STF_Lethal_Decoy(void)
{
	m_eStateType = STATE_TYPE_MONK_MALE_STF_LETGAL_DECOY;
}

CMonk_Male_STF_Lethal_Decoy::~CMonk_Male_STF_Lethal_Decoy(void)
{
}

void CMonk_Male_STF_Lethal_Decoy::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(54);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CMonk_Male_STF_Lethal_Decoy::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CMonk_Male_STF_Idle;	
	}
	return NULL;
}
