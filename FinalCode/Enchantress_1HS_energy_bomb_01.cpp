#include "StdAfx.h"
#include "Enchantress_1HS_energy_bomb_01.h"

CEnchantress_1HS_energy_bomb_01::CEnchantress_1HS_energy_bomb_01(int _iMode)
: CFollowerState(_iMode)
{
	// StateType
	m_eStateType = STATE_TYPE_ENCHANTRESS_1HS_ENERGY_BOMB_01;
}

CEnchantress_1HS_energy_bomb_01::~CEnchantress_1HS_energy_bomb_01()
{
}

void CEnchantress_1HS_energy_bomb_01::Initialize()
{
	// Initialize
	CFollowerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(62);
}

CFollowerState* CEnchantress_1HS_energy_bomb_01::Action()
{
	return NULL;
}
