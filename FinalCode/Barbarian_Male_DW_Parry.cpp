#include "StdAfx.h"
#include "Barbarian_Male_DW_Parry.h"

CBarbarian_Male_DW_Parry::CBarbarian_Male_DW_Parry(void)
{
	m_eStateType = STATE_TYPE_BARBARIAN_MALE_DW_PARRY;
}

CBarbarian_Male_DW_Parry::~CBarbarian_Male_DW_Parry(void)
{
}

void CBarbarian_Male_DW_Parry::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(42);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CBarbarian_Male_DW_Parry::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CBarbarian_Male_DW_Idle;	
	}
	return NULL;
}
