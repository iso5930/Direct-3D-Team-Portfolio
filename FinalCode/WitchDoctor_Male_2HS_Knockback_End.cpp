#include "StdAfx.h"
#include "WitchDoctor_Male_2HS_Knockback_End.h"

CWitchDoctor_Male_2HS_Knockback_End::CWitchDoctor_Male_2HS_Knockback_End(void)
{
	m_eStateType = STATE_TYPE_WITCHDOCTOR_MALE_2HS_KNOCKBACK_END;
}

CWitchDoctor_Male_2HS_Knockback_End::~CWitchDoctor_Male_2HS_Knockback_End(void)
{
}

void CWitchDoctor_Male_2HS_Knockback_End::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(31);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CWitchDoctor_Male_2HS_Knockback_End::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CWitchDoctor_Male_2HS_Idle;	
	}
	return NULL;
}
