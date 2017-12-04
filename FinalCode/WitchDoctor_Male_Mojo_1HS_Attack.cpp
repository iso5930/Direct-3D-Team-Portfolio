#include "StdAfx.h"
#include "WitchDoctor_Male_Mojo_1HS_Attack.h"

CWitchDoctor_Male_Mojo_1HS_Attack::CWitchDoctor_Male_Mojo_1HS_Attack(void)
{
	m_eStateType = STATE_TYPE_WITCHDOCTOR_MALE_MOJO_1HS_ATTACK;
}

CWitchDoctor_Male_Mojo_1HS_Attack::~CWitchDoctor_Male_Mojo_1HS_Attack(void)
{
}

void CWitchDoctor_Male_Mojo_1HS_Attack::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(61);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CWitchDoctor_Male_Mojo_1HS_Attack::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CWitchDoctor_Male_Mojo_1HS_Idle;	
	}
	return NULL;
}
