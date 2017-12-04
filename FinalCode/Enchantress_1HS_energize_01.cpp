#include "StdAfx.h"
#include "Enchantress_1HS_energize_01.h"

CEnchantress_1HS_energize_01::CEnchantress_1HS_energize_01(int _iMode)
: CFollowerState(_iMode)
{
	// StateType
	m_eStateType = STATE_TYPE_ENCHANTRESS_1HS_ENERGIZE_01;
}

CEnchantress_1HS_energize_01::~CEnchantress_1HS_energize_01()
{
}

void CEnchantress_1HS_energize_01::Initialize()
{
	// Initialize
	CFollowerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(63);
}

CFollowerState* CEnchantress_1HS_energize_01::Action()
{
	return NULL;
}
