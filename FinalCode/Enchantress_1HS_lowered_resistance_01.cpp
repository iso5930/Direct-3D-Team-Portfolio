#include "StdAfx.h"
#include "Enchantress_1HS_lowered_resistance_01.h"

CEnchantress_1HS_lowered_resistance_01::CEnchantress_1HS_lowered_resistance_01(int _iMode)
: CFollowerState(_iMode)
{
	// StateType
	m_eStateType = STATE_TYPE_ENCHANTRESS_1HS_LOWERED_RESISTANCE_01;
}

CEnchantress_1HS_lowered_resistance_01::~CEnchantress_1HS_lowered_resistance_01()
{
}

void CEnchantress_1HS_lowered_resistance_01::Initialize()
{
	// Initialize
	CFollowerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(56);
}

CFollowerState* CEnchantress_1HS_lowered_resistance_01::Action()
{
	return NULL;
}
