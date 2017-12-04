#include "StdAfx.h"
#include "Barbarian_Male_DW_Cleave01.h"

CBarbarian_Male_DW_Cleave01::CBarbarian_Male_DW_Cleave01(void)
{
	m_eStateType = STATE_TYPE_BARBARIAN_MALE_DW_CLEAVE01;
}

CBarbarian_Male_DW_Cleave01::~CBarbarian_Male_DW_Cleave01(void)
{
}

void CBarbarian_Male_DW_Cleave01::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(90);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CBarbarian_Male_DW_Cleave01::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CBarbarian_Male_DW_Idle;	
	}
	return NULL;
}
