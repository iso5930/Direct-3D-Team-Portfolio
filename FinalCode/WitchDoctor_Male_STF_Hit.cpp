#include "StdAfx.h"
#include "WitchDoctor_Male_STF_Hit.h"

CWitchDoctor_Male_STF_Hit::CWitchDoctor_Male_STF_Hit(void)
{
	m_eStateType = STATE_TYPE_WITCHDOCTOR_MALE_STF_HIT;
}

CWitchDoctor_Male_STF_Hit::~CWitchDoctor_Male_STF_Hit(void)
{
}

void CWitchDoctor_Male_STF_Hit::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(47);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CWitchDoctor_Male_STF_Hit::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CWitchDoctor_Male_STF_Idle;	
	}
	return NULL;
}
