#include "StdAfx.h"
#include "Barbarian_Male_2HS_Attack.h"

CBarbarian_Male_2HS_Attack::CBarbarian_Male_2HS_Attack(void)
{
	m_eStateType = STATE_TYPE_BARBARIAN_MALE_2HS_ATTACK;
}

CBarbarian_Male_2HS_Attack::~CBarbarian_Male_2HS_Attack(void)
{
}

void CBarbarian_Male_2HS_Attack::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(106);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CBarbarian_Male_2HS_Attack::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CBarbarian_Male_2HS_Idle;	
	}
	return NULL;
}
