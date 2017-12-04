#include "StdAfx.h"
#include "Monk_Male_DW_FF_Buff.h"

CMonk_Male_DW_FF_Buff::CMonk_Male_DW_FF_Buff(void)
{
	m_eStateType = STATE_TYPE_MONK_MALE_DW_FF_BUFF;
}

CMonk_Male_DW_FF_Buff::~CMonk_Male_DW_FF_Buff(void)
{
}

void CMonk_Male_DW_FF_Buff::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(52);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CMonk_Male_DW_FF_Buff::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CMonk_Male_DW_FF_Idle;	
	}
	return NULL;
}
