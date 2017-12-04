#include "StdAfx.h"
#include "WitchDoctor_Male_2HS_Stunned.h"

CWitchDoctor_Male_2HS_Stunned::CWitchDoctor_Male_2HS_Stunned(void)
{
	m_eStateType = STATE_TYPE_WITCHDOCTOR_MALE_2HS_STUNNED;
}

CWitchDoctor_Male_2HS_Stunned::~CWitchDoctor_Male_2HS_Stunned(void)
{
}

void CWitchDoctor_Male_2HS_Stunned::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(22);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CWitchDoctor_Male_2HS_Stunned::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CWitchDoctor_Male_2HS_Idle;	
	}
	return NULL;
}
