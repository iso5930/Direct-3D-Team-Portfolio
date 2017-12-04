#include "StdAfx.h"
#include "Barbarian_Male_1HT_Cleave01.h"

CBarbarian_Male_1HT_Cleave01::CBarbarian_Male_1HT_Cleave01(void)
{
	m_eStateType = STATE_TYPE_BARBARIAN_MALE_1HT_CLEAVE01;
}

CBarbarian_Male_1HT_Cleave01::~CBarbarian_Male_1HT_Cleave01(void)
{
}

void CBarbarian_Male_1HT_Cleave01::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(84);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CBarbarian_Male_1HT_Cleave01::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CBarbarian_Male_1HT_Idle;	
	}
	return NULL;
}
