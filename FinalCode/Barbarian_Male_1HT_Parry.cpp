#include "StdAfx.h"
#include "Barbarian_Male_1HT_Parry.h"

CBarbarian_Male_1HT_Parry::CBarbarian_Male_1HT_Parry(void)
{
	m_eStateType = STATE_TYPE_BARBARIAN_MALE_1HT_PARRY;
}

CBarbarian_Male_1HT_Parry::~CBarbarian_Male_1HT_Parry(void)
{
}

void CBarbarian_Male_1HT_Parry::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(46);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CBarbarian_Male_1HT_Parry::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CBarbarian_Male_1HT_Idle;	
	}
	return NULL;
}
