#include "StdAfx.h"
#include "Barbarian_Male_DW_Attack_L.h"

CBarbarian_Male_DW_Attack_L::CBarbarian_Male_DW_Attack_L(void)
{
	m_eStateType = STATE_TYPE_BARBARIAN_MALE_DW_ATTACK_L;
}

CBarbarian_Male_DW_Attack_L::~CBarbarian_Male_DW_Attack_L(void)
{
}

void CBarbarian_Male_DW_Attack_L::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(102);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CBarbarian_Male_DW_Attack_L::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CBarbarian_Male_DW_Idle;	
	}
	return NULL;
}
