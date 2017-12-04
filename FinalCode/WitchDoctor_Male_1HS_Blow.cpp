#include "StdAfx.h"
#include "WitchDoctor_Male_1HS_Blow.h"

CWitchDoctor_Male_1HS_Blow::CWitchDoctor_Male_1HS_Blow(void)
{
	m_eStateType = STATE_TYPE_WITCHDOCTOR_MALE_1HS_BLOW;
}

CWitchDoctor_Male_1HS_Blow::~CWitchDoctor_Male_1HS_Blow(void)
{
}

void CWitchDoctor_Male_1HS_Blow::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(69);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CWitchDoctor_Male_1HS_Blow::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CWitchDoctor_Male_1HS_Idle;	
	}

	return NULL;
}
