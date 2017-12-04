#include "StdAfx.h"
#include "Monk_Male_1HS_Buff.h"

CMonk_Male_1HS_Buff::CMonk_Male_1HS_Buff(void)
{
	m_eStateType = STATE_TYPE_MONK_MALE_1HS_BUFF;
}

CMonk_Male_1HS_Buff::~CMonk_Male_1HS_Buff(void)
{
}

void CMonk_Male_1HS_Buff::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(52);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CMonk_Male_1HS_Buff::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CMonk_Male_1HS_Idle;	
	}
	return NULL;
}
