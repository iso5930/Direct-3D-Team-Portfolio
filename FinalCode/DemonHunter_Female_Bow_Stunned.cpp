#include "StdAfx.h"
#include "DemonHunter_Female_Bow_Stunned.h"

CDemonHunter_Female_Bow_Stunned::CDemonHunter_Female_Bow_Stunned()
{
	// StateType
	m_eStateType = STATE_TYPE_DEMONHUNTER_FEMALE_BOW_STUNNED;
}

CDemonHunter_Female_Bow_Stunned::~CDemonHunter_Female_Bow_Stunned()
{
}

void CDemonHunter_Female_Bow_Stunned::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(38);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CDemonHunter_Female_Bow_Stunned::Action()
{

	return NULL;
}


