#include "StdAfx.h"
#include "WitchDoctor_Male_STF_Attack.h"

CWitchDoctor_Male_STF_Attack::CWitchDoctor_Male_STF_Attack(void)
{
	m_eStateType = STATE_TYPE_WITCHDOCTOR_MALE_STF_ATTACK;
}

CWitchDoctor_Male_STF_Attack::~CWitchDoctor_Male_STF_Attack(void)
{
}

void CWitchDoctor_Male_STF_Attack::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(56);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CWitchDoctor_Male_STF_Attack::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CWitchDoctor_Male_STF_Idle;	
	}
	return NULL;
}
