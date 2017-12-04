#include "StdAfx.h"
#include "Wizard_Female_1HS_AOE.h"

CBarbarian_Male_1HS_Parry::CBarbarian_Male_1HS_Parry(void)
{
	m_eStateType = STATE_TYPE_BARBARIAN_MALE_1HS_PARRY;
}

CBarbarian_Male_1HS_Parry::~CBarbarian_Male_1HS_Parry(void)
{
}

void CBarbarian_Male_1HS_Parry::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(47);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CBarbarian_Male_1HS_Parry::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CBarbarian_Male_1HS_Idle;	
	}
	return NULL;
}
