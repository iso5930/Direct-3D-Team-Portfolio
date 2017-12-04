#include "StdAfx.h"
#include "Monk_Male_2HT_Buff.h"

CMonk_Male_2HT_Buff::CMonk_Male_2HT_Buff(void)
{
	m_eStateType = STATE_TYPE_MONK_MALE_2HT_BUFF;
}

CMonk_Male_2HT_Buff::~CMonk_Male_2HT_Buff(void)
{
}

void CMonk_Male_2HT_Buff::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(52);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CMonk_Male_2HT_Buff::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CMonk_Male_2HT_Idle;	
	}
	return NULL;
}