#include "StdAfx.h"
#include "Barbarian_Male_DW_Revenge.h"

CBarbarian_Male_DW_Revenge::CBarbarian_Male_DW_Revenge(void)
{
	m_eStateType = STATE_TYPE_BARBARIAN_MALE_DW_REVENGE;
}

CBarbarian_Male_DW_Revenge::~CBarbarian_Male_DW_Revenge(void)
{
}

void CBarbarian_Male_DW_Revenge::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(36);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CBarbarian_Male_DW_Revenge::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CBarbarian_Male_DW_Idle;	
	}
	return NULL;
}
