#include "StdAfx.h"
#include "Barbarian_Male_2HT_Revenge.h"

CBarbarian_Male_2HT_Revenge::CBarbarian_Male_2HT_Revenge(void)
{
	m_eStateType = STATE_TYPE_WIZARD_FEMALE_2HS_AOE;
}

CBarbarian_Male_2HT_Revenge::~CBarbarian_Male_2HT_Revenge(void)
{
}

void CBarbarian_Male_2HT_Revenge::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(38);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CBarbarian_Male_2HT_Revenge::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CBarbarian_Male_2HT_Idle;	
	}
	return NULL;
}
