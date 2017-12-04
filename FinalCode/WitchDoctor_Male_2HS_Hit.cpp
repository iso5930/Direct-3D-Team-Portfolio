#include "StdAfx.h"
#include "WitchDoctor_Male_2HS_Hit.h"

CWitchDoctor_Male_2HS_Hit::CWitchDoctor_Male_2HS_Hit(void)
{
	m_eStateType = STATE_TYPE_WITCHDOCTOR_MALE_2HS_HIT;
}

CWitchDoctor_Male_2HS_Hit::~CWitchDoctor_Male_2HS_Hit(void)
{
}

void CWitchDoctor_Male_2HS_Hit::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(49);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CWitchDoctor_Male_2HS_Hit::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CWitchDoctor_Male_2HS_Idle;	
	}
	return NULL;
}
