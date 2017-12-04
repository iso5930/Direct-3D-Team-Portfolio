#include "StdAfx.h"
#include "Wizard_Female_1HS_AOE.h"

CBarbarian_Male_1HS_Revenge::CBarbarian_Male_1HS_Revenge(void)
{
	m_eStateType = STATE_TYPE_BARBARIAN_MALE_1HS_REVENGE;

	m_iMode = 0 ;

	m_fTime = 0.0f;
}

CBarbarian_Male_1HS_Revenge::~CBarbarian_Male_1HS_Revenge(void)
{
}

void CBarbarian_Male_1HS_Revenge::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(41);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CBarbarian_Male_1HS_Revenge::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		m_pOwner->RemoveAttack();

		return new CBarbarian_Male_1HS_Idle;	
	}

	switch(m_iMode)
	{
	case 0:
		return Mode0();
	
	case 1:
		return Mode1();
	}



	return NULL;
}

CPlayerState* CBarbarian_Male_1HS_Revenge::Mode0()
{
	++m_iMode;
	m_fTime = 0.0f;
	m_pOwner->CreateAttack();
	return NULL;
}

CPlayerState* CBarbarian_Male_1HS_Revenge::Mode1()
{
	return NULL;
}
