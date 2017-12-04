#include "StdAfx.h"
#include "Barbarian_Male_1HT_Revenge.h"

CBarbarian_Male_1HT_Revenge::CBarbarian_Male_1HT_Revenge(void)
{
	m_eStateType = STATE_TYPE_BARBARIAN_MALE_1HT_REVENGE;
}

CBarbarian_Male_1HT_Revenge::~CBarbarian_Male_1HT_Revenge(void)
{
}

void CBarbarian_Male_1HT_Revenge::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(40);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CBarbarian_Male_1HT_Revenge::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CBarbarian_Male_1HT_Idle;	
	}
	return NULL;
}
