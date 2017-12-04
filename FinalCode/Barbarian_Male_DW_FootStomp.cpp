#include "StdAfx.h"
#include "Barbarian_Male_DW_FootStomp.h"

CBarbarian_Male_DW_FootStomp::CBarbarian_Male_DW_FootStomp(void)
{
	m_eStateType = STATE_TYPE_BARBARIAN_MALE_DW_FOOTSTOMP;
}

CBarbarian_Male_DW_FootStomp::~CBarbarian_Male_DW_FootStomp(void)
{
}

void CBarbarian_Male_DW_FootStomp::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(78);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CBarbarian_Male_DW_FootStomp::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CBarbarian_Male_DW_Idle;	
	}
	return NULL;
}
