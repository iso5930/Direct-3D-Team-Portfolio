#include "StdAfx.h"
#include "Wizard_Female_Bow_Range_Attack.h"

CWizard_Female_Bow_Range_Attack::CWizard_Female_Bow_Range_Attack(void)
{
	m_eStateType = STATE_TYPE_WIZARD_FEMALE_BOW_RANGE_ATTACK;
}

CWizard_Female_Bow_Range_Attack::~CWizard_Female_Bow_Range_Attack(void)
{
}

void CWizard_Female_Bow_Range_Attack::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(43);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CWizard_Female_Bow_Range_Attack::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CWizard_Female_Bow_Idle;
	}

	return NULL;
}