#include "StdAfx.h"
#include "Barbarian_Male_1HS_Buff.h"

CBarbarian_Male_1HS_Buff::CBarbarian_Male_1HS_Buff(void)
{
	m_eStateType = STATE_TYPE_BARBARIAN_MALE_1HS_BUFF;
}

CBarbarian_Male_1HS_Buff::~CBarbarian_Male_1HS_Buff(void)
{
}

void CBarbarian_Male_1HS_Buff::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(101);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CBarbarian_Male_1HS_Buff::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CBarbarian_Male_1HS_Idle;	
	}
	return NULL;
}