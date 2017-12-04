#include "StdAfx.h"
#include "Enchantress_STF_enchantress_parry_01.h"

CEnchantress_STF_enchantress_parry_01::CEnchantress_STF_enchantress_parry_01(int _iMode)
: CFollowerState(_iMode)
{
	// StateType
	m_eStateType = STATE_TYPE_ENCHANTRESS_STF_ENCHANTRESS_PARRY_01;
}

CEnchantress_STF_enchantress_parry_01::~CEnchantress_STF_enchantress_parry_01()
{
}

void CEnchantress_STF_enchantress_parry_01::Initialize()
{
	// Initialize
	CFollowerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(3);
}

CFollowerState* CEnchantress_STF_enchantress_parry_01::Action()
{
	return NULL;
}
