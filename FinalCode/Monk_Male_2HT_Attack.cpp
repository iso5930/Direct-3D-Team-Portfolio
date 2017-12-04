#include "StdAfx.h"
#include "Monk_Male_2HT_Attack.h"

CMonk_Male_2HT_Attack::CMonk_Male_2HT_Attack(void)
{
	m_eStateType = STATE_TYPE_MONK_MALE_2HT_ATTACK;
}

CMonk_Male_2HT_Attack::~CMonk_Male_2HT_Attack(void)
{
}

void CMonk_Male_2HT_Attack::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(49);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CMonk_Male_2HT_Attack::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CMonk_Male_2HT_Idle;	
	}
	return NULL;
}
