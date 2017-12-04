#include "StdAfx.h"
#include "WitchDoctor_Male_STF_Stunned.h"

CWitchDoctor_Male_STF_Stunned::CWitchDoctor_Male_STF_Stunned(void)
{
	m_eStateType = STATE_TYPE_WITCHDOCTOR_MALE_STF_STUNNED;
}

CWitchDoctor_Male_STF_Stunned::~CWitchDoctor_Male_STF_Stunned(void)
{
}

void CWitchDoctor_Male_STF_Stunned::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(20);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CWitchDoctor_Male_STF_Stunned::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CWitchDoctor_Male_STF_Idle;	
	}
	return NULL;
}
