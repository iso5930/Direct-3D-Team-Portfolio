#include "StdAfx.h"
#include "Barbarian_Male_DW_Hit.h"

CBarbarian_Male_DW_Hit::CBarbarian_Male_DW_Hit(void)
{
	m_eStateType = STATE_TYPE_BARBARIAN_MALE_DW_HIT;
}

CBarbarian_Male_DW_Hit::~CBarbarian_Male_DW_Hit(void)
{
}

void CBarbarian_Male_DW_Hit::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(60);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CBarbarian_Male_DW_Hit::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CBarbarian_Male_DW_Idle;	
	}
	return NULL;
}
