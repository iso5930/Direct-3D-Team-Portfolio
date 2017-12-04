#include "StdAfx.h"
#include "WitchDoctor_Male_1HS_Hit.h"

CWitchDoctor_Male_1HS_Hit::CWitchDoctor_Male_1HS_Hit(void)
{
	m_eStateType = STATE_TYPE_WITCHDOCTOR_MALE_1HS_HIT;
}

CWitchDoctor_Male_1HS_Hit::~CWitchDoctor_Male_1HS_Hit(void)
{
}

void CWitchDoctor_Male_1HS_Hit::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(53);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CWitchDoctor_Male_1HS_Hit::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CWitchDoctor_Male_1HS_Idle;	
	}
	return NULL;
}
