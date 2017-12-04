#include "StdAfx.h"
#include "WitchDoctor_Male_Bow_Stunned.h"

CWitchDoctor_Male_Bow_Stunned::CWitchDoctor_Male_Bow_Stunned(void)
{
	m_eStateType = STATE_TYPE_WITCHDOCTOR_MALE_BOW_STUNNED;
}

CWitchDoctor_Male_Bow_Stunned::~CWitchDoctor_Male_Bow_Stunned(void)
{
}

void CWitchDoctor_Male_Bow_Stunned::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(19);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CWitchDoctor_Male_Bow_Stunned::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CWitchDoctor_Male_Bow_Idle;	
	}
	return NULL;
}
