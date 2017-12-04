#include "StdAfx.h"
#include "Barbarian_Male_2HS_Parry.h"

CBarbarian_Male_2HS_Parry::CBarbarian_Male_2HS_Parry(void)
{
	m_eStateType = STATE_TYPE_BARBARIAN_MALE_2HS_PARRY;
}

CBarbarian_Male_2HS_Parry::~CBarbarian_Male_2HS_Parry(void)
{
}

void CBarbarian_Male_2HS_Parry::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(45);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CBarbarian_Male_2HS_Parry::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CBarbarian_Male_2HS_Idle;	
	}
	return NULL;
}
