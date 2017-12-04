#include "StdAfx.h"
#include "WitchDoctor_Male_2HS_Horrify.h"

CWitchDoctor_Male_2HS_Horrify::CWitchDoctor_Male_2HS_Horrify(void)
{
	m_eStateType = STATE_TYPE_WITCHDOCTOR_MALE_2HS_HORRIFY;
}

CWitchDoctor_Male_2HS_Horrify::~CWitchDoctor_Male_2HS_Horrify(void)
{
}

void CWitchDoctor_Male_2HS_Horrify::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(71);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CWitchDoctor_Male_2HS_Horrify::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CWitchDoctor_Male_2HS_Idle;	
	}
	return NULL;
}