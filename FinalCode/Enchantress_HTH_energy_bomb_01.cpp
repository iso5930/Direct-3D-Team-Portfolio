#include "StdAfx.h"
#include "Enchantress_HTH_energy_bomb_01.h"

CEnchantress_HTH_energy_bomb_01::CEnchantress_HTH_energy_bomb_01(int _iMode)
: CFollowerState(_iMode)
{
	// StateType
	m_eStateType = STATE_TYPE_ENCHANTRESS_HTH_ENERGY_BOMB_01;
}

CEnchantress_HTH_energy_bomb_01::~CEnchantress_HTH_energy_bomb_01()
{
}

void CEnchantress_HTH_energy_bomb_01::Initialize()
{
	// Initialize
	CFollowerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(30);
}

CFollowerState* CEnchantress_HTH_energy_bomb_01::Action()
{
	return NULL;
}
