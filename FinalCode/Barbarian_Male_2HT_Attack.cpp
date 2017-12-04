#include "StdAfx.h"
#include "Barbarian_Male_2HT_Attack.h"

CBarbarian_Male_2HT_Attack::CBarbarian_Male_2HT_Attack(void)
{
	m_eStateType = STATE_TYPE_BARBARIAN_MALE_2HT_ATTACK;
}

CBarbarian_Male_2HT_Attack::~CBarbarian_Male_2HT_Attack(void)
{
}

void CBarbarian_Male_2HT_Attack::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(105);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CBarbarian_Male_2HT_Attack::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CBarbarian_Male_2HT_Idle;	
	}
	return NULL;
}
