#include "StdAfx.h"
#include "Wizard_Female_1HS_KnockbackEnd.h"

CWizard_Female_1HS_KnockbackEnd::CWizard_Female_1HS_KnockbackEnd(void)
{
	m_eStateType = STATE_TYPE_WIZARD_FEMALE_1HS_KNOCKBACK_END;
}

CWizard_Female_1HS_KnockbackEnd::~CWizard_Female_1HS_KnockbackEnd(void)
{
}

void CWizard_Female_1HS_KnockbackEnd::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(30);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CWizard_Female_1HS_KnockbackEnd::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CWizard_Female_1HS_Idle;	
	}

	return NULL;
}