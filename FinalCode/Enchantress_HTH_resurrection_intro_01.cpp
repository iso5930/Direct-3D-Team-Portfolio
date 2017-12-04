#include "StdAfx.h"
#include "Enchantress_HTH_resurrection_intro_01.h"

CEnchantress_HTH_resurrection_intro_01::CEnchantress_HTH_resurrection_intro_01(int _iMode)
: CFollowerState(_iMode)
{
	// StateType
	m_eStateType = STATE_TYPE_ENCHANTRESS_HTH_RESURRECTION_INTRO_01;
}

CEnchantress_HTH_resurrection_intro_01::~CEnchantress_HTH_resurrection_intro_01()
{
}

void CEnchantress_HTH_resurrection_intro_01::Initialize()
{
	// Initialize
	CFollowerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(21);
}

CFollowerState* CEnchantress_HTH_resurrection_intro_01::Action()
{
	return NULL;
}
