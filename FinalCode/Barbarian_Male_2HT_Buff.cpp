#include "StdAfx.h"
#include "Barbarian_Male_2HT_Buff.h"

CBarbarian_Male_2HT_Buff::CBarbarian_Male_2HT_Buff(void)
{
	m_eStateType = STATE_TYPE_BARBARIAN_MALE_2HT_BUFF;
}

CBarbarian_Male_2HT_Buff::~CBarbarian_Male_2HT_Buff(void)
{
}

void CBarbarian_Male_2HT_Buff::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(98);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CBarbarian_Male_2HT_Buff::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CBarbarian_Male_2HT_Idle;	
	}
	return NULL;
}
