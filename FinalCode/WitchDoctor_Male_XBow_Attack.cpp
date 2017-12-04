#include "StdAfx.h"
#include "WitchDoctor_Male_XBow_Attack.h"

CWitchDoctor_Male_XBow_Attack::CWitchDoctor_Male_XBow_Attack(void)
{
	m_eStateType = STATE_TYPE_WITCHDOCTOR_MALE_XBOW_ATTACK;
}

CWitchDoctor_Male_XBow_Attack::~CWitchDoctor_Male_XBow_Attack(void)
{
}

void CWitchDoctor_Male_XBow_Attack::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(54);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CWitchDoctor_Male_XBow_Attack::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CWitchDoctor_Male_XBow_Idle;	
	}
	return NULL;
}
