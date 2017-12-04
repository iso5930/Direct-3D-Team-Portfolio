#include "StdAfx.h"
#include "Barbarian_Male_1HT_Attack.h"

CBarbarian_Male_1HT_Attack::CBarbarian_Male_1HT_Attack(void)
{
	m_eStateType = STATE_TYPE_BARBARIAN_MALE_1HT_ATTACK;
}

CBarbarian_Male_1HT_Attack::~CBarbarian_Male_1HT_Attack(void)
{
}

void CBarbarian_Male_1HT_Attack::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(107);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CBarbarian_Male_1HT_Attack::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CBarbarian_Male_1HT_Idle;	
	}
	return NULL;
}
