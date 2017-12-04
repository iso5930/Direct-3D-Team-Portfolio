#include "StdAfx.h"
#include "Monk_Male_1HT_Lightning_03.h"

CMonk_Male_1HT_Lightning_03::CMonk_Male_1HT_Lightning_03(void)
{
	m_eStateType = STATE_TYPE_MONK_MALE_1HT_LIGHTNING_03;
}

CMonk_Male_1HT_Lightning_03::~CMonk_Male_1HT_Lightning_03(void)
{
}

void CMonk_Male_1HT_Lightning_03::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(57);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CMonk_Male_1HT_Lightning_03::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CMonk_Male_1HT_Idle;	
	}
	return NULL;
}
