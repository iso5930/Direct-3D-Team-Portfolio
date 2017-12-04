#include "StdAfx.h"
#include "Barbarian_Male_STF_Revenge.h"

CBarbarian_Male_STF_Revenge::CBarbarian_Male_STF_Revenge(void)
{
	m_eStateType = STATE_TYPE_BARBARIAN_MALE_STF_REVENGE;
}

CBarbarian_Male_STF_Revenge::~CBarbarian_Male_STF_Revenge(void)
{
}

void CBarbarian_Male_STF_Revenge::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(37);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CBarbarian_Male_STF_Revenge::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CBarbarian_Male_STF_Idle;	
	}
	return NULL;
}
