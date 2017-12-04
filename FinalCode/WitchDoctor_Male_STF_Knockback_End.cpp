#include "StdAfx.h"
#include "WitchDoctor_Male_STF_Knockback_End.h"

CWitchDoctor_Male_STF_Knockback_End::CWitchDoctor_Male_STF_Knockback_End(void)
{
	m_eStateType = STATE_TYPE_WITCHDOCTOR_MALE_STF_KNOCKBACK_END;
}

CWitchDoctor_Male_STF_Knockback_End::~CWitchDoctor_Male_STF_Knockback_End(void)
{
}

void CWitchDoctor_Male_STF_Knockback_End::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(29);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CWitchDoctor_Male_STF_Knockback_End::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CWitchDoctor_Male_STF_Idle;	
	}
	return NULL;
}
