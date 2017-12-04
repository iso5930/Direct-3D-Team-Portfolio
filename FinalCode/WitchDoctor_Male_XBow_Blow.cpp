#include "StdAfx.h"
#include "WitchDoctor_Male_XBow_Blow.h"

CWitchDoctor_Male_XBow_Blow::CWitchDoctor_Male_XBow_Blow(void)
{
	m_eStateType = STATE_TYPE_WITCHDOCTOR_MALE_XBOW_BLOW;
}

CWitchDoctor_Male_XBow_Blow::~CWitchDoctor_Male_XBow_Blow(void)
{
}

void CWitchDoctor_Male_XBow_Blow::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(69);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CWitchDoctor_Male_XBow_Blow::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CWitchDoctor_Male_XBow_Idle;	
	}
	return NULL;
}
