#include "StdAfx.h"
#include "WitchDoctor_Male_STF_Horrify.h"

CWitchDoctor_Male_STF_Horrify::CWitchDoctor_Male_STF_Horrify(void)
{
	m_eStateType = STATE_TYPE_WITCHDOCTOR_MALE_STF_HORRIFY;
}

CWitchDoctor_Male_STF_Horrify::~CWitchDoctor_Male_STF_Horrify(void)
{
}

void CWitchDoctor_Male_STF_Horrify::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(71);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CWitchDoctor_Male_STF_Horrify::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CWitchDoctor_Male_STF_Idle;	
	}
	return NULL;
}