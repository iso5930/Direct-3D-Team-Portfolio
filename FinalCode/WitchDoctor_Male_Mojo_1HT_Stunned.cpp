#include "StdAfx.h"
#include "WitchDoctor_Male_Mojo_1HT_Stunned.h"

CWitchDoctor_Male_Mojo_1HT_Stunned::CWitchDoctor_Male_Mojo_1HT_Stunned(void)
{
	m_eStateType = STATE_TYPE_WITCHDOCTOR_MALE_MOJO_1HT_STUNNED;
}

CWitchDoctor_Male_Mojo_1HT_Stunned::~CWitchDoctor_Male_Mojo_1HT_Stunned(void)
{
}

void CWitchDoctor_Male_Mojo_1HT_Stunned::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(23);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CWitchDoctor_Male_Mojo_1HT_Stunned::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CWitchDoctor_Male_Mojo_1HT_Idle;	
	}
	return NULL;
}
