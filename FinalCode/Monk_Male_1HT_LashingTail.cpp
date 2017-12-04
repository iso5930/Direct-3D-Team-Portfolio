#include "StdAfx.h"
#include "Monk_Male_1HT_LashingTail.h"

CMonk_Male_1HT_LashingTail::CMonk_Male_1HT_LashingTail(void)
{
	m_eStateType = STATE_TYPE_MONK_MALE_1HT_LASHINGTAIL;
}

CMonk_Male_1HT_LashingTail::~CMonk_Male_1HT_LashingTail(void)
{
}

void CMonk_Male_1HT_LashingTail::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(55);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CMonk_Male_1HT_LashingTail::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CMonk_Male_1HT_Idle;	
	}
	return NULL;
}
