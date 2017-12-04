#include "StdAfx.h"
#include "Barbarian_Male_2HT_Cleave02.h"

CBarbarian_Male_2HT_Cleave02::CBarbarian_Male_2HT_Cleave02(void)
{
	m_eStateType = STATE_TYPE_WIZARD_FEMALE_2HS_AOE;
}

CBarbarian_Male_2HT_Cleave02::~CBarbarian_Male_2HT_Cleave02(void)
{
}

void CBarbarian_Male_2HT_Cleave02::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(86);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CBarbarian_Male_2HT_Cleave02::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CBarbarian_Male_2HT_Idle;	
	}
	return NULL;
}
