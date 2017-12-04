#include "StdAfx.h"
#include "Wizard_Female_1HS_Orb_KnockbackEnd.h"

CWizard_Female_1HS_Orb_KnockbackEnd::CWizard_Female_1HS_Orb_KnockbackEnd()
{
	m_eStateType = STATE_TYPE_WIZARD_FEMALE_1HS_ORB_KNOCKBACK_END;
}
CWizard_Female_1HS_Orb_KnockbackEnd::~CWizard_Female_1HS_Orb_KnockbackEnd()
{

}

void CWizard_Female_1HS_Orb_KnockbackEnd::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(29);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CWizard_Female_1HS_Orb_KnockbackEnd::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CWizard_Female_1HS_Orb_Idle;
	}

	return NULL;
}