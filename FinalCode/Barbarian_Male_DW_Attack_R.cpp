#include "StdAfx.h"
#include "Barbarian_Male_DW_Attack_R.h"

CBarbarian_Male_DW_Attack_R::CBarbarian_Male_DW_Attack_R(void)
{
	m_eStateType = STATE_TYPE_BARBARIAN_MALE_DW_ATTACK_R;
}

CBarbarian_Male_DW_Attack_R::~CBarbarian_Male_DW_Attack_R(void)
{
}

void CBarbarian_Male_DW_Attack_R::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(103);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CBarbarian_Male_DW_Attack_R::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CBarbarian_Male_DW_Idle;	
	}
	return NULL;
}
