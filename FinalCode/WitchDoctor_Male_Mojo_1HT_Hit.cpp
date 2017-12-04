#include "StdAfx.h"
#include "WitchDoctor_Male_Mojo_1HT_Hit.h"

CWitchDoctor_Male_Mojo_1HT_Hit::CWitchDoctor_Male_Mojo_1HT_Hit(void)
{
	m_eStateType = STATE_TYPE_WITCHDOCTOR_MALE_MOJO_1HT_HIT;
}

CWitchDoctor_Male_Mojo_1HT_Hit::~CWitchDoctor_Male_Mojo_1HT_Hit(void)
{
}

void CWitchDoctor_Male_Mojo_1HT_Hit::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(50);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CWitchDoctor_Male_Mojo_1HT_Hit::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CWitchDoctor_Male_Mojo_1HT_Idle;	
	}
	return NULL;
}
