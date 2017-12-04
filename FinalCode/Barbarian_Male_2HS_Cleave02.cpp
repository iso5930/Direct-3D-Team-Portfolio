#include "StdAfx.h"
#include "Barbarian_Male_2HS_Cleave02.h"

CBarbarian_Male_2HS_Cleave02::CBarbarian_Male_2HS_Cleave02(void)
{
	m_eStateType = STATE_TYPE_BARBARIAN_MALE_2HS_CLEAVE02;
}

CBarbarian_Male_2HS_Cleave02::~CBarbarian_Male_2HS_Cleave02(void)
{
}

void CBarbarian_Male_2HS_Cleave02::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(87);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CBarbarian_Male_2HS_Cleave02::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CBarbarian_Male_2HS_Idle;	
	}
	return NULL;
}
