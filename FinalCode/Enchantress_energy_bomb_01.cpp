#include "StdAfx.h"
#include "Enchantress_energy_bomb_01.h"

CEnchantress_energy_bomb_01::CEnchantress_energy_bomb_01(int _iMode)
: CFollowerState(_iMode)
{
	// StateType
	m_eStateType = STATE_TYPE_ENCHANTRESS_ENERGY_BOMB_01;
}

CEnchantress_energy_bomb_01::~CEnchantress_energy_bomb_01()
{
}

void CEnchantress_energy_bomb_01::Initialize()
{
	// Initialize
	CFollowerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(39);
}

CFollowerState* CEnchantress_energy_bomb_01::Action()
{
	return NULL;
}
