#include "StdAfx.h"
#include "Enchantress_HTH_lowered_resistance_01.h"

CEnchantress_HTH_lowered_resistance_01::CEnchantress_HTH_lowered_resistance_01(int _iMode)
: CFollowerState(_iMode)
{
	// StateType
	m_eStateType = STATE_TYPE_ENCHANTRESS_HTH_LOWERED_RESISTANCE_01;
}

CEnchantress_HTH_lowered_resistance_01::~CEnchantress_HTH_lowered_resistance_01()
{
}

void CEnchantress_HTH_lowered_resistance_01::Initialize()
{
	// Initialize
	CFollowerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(25);
}

CFollowerState* CEnchantress_HTH_lowered_resistance_01::Action()
{
	return NULL;
}
