#include "StdAfx.h"
#include "WitchDoctor_Male_XBow_AcidCloud_barf.h"

CWitchDoctor_Male_XBow_AcidCloud_barf::CWitchDoctor_Male_XBow_AcidCloud_barf(void)
{
	m_eStateType = STATE_TYPE_WITCHDOCTOR_MALE_XBOW_ACIDCLOUD_BARF;
}

CWitchDoctor_Male_XBow_AcidCloud_barf::~CWitchDoctor_Male_XBow_AcidCloud_barf(void)
{
}

void CWitchDoctor_Male_XBow_AcidCloud_barf::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(74);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CWitchDoctor_Male_XBow_AcidCloud_barf::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CWitchDoctor_Male_XBow_Idle;	
	}
	return NULL;
}