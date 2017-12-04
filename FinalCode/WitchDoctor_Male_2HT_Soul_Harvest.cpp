#include "StdAfx.h"
#include "WitchDoctor_Male_2HT_Soul_Harvest.h"

CWitchDoctor_Male_2HT_Soul_Harvest::CWitchDoctor_Male_2HT_Soul_Harvest(void)
{
	m_eStateType = STATE_TYPE_WITCHDOCTOR_MALE_2HT_SOUL_HARVEST;
}

CWitchDoctor_Male_2HT_Soul_Harvest::~CWitchDoctor_Male_2HT_Soul_Harvest(void)
{
}

void CWitchDoctor_Male_2HT_Soul_Harvest::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(70);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CWitchDoctor_Male_2HT_Soul_Harvest::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CWitchDoctor_Male_2HT_Idle;	
	}
	return NULL;
}
