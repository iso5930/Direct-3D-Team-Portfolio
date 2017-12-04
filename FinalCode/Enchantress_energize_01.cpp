#include "StdAfx.h"
#include "Enchantress_energize_01.h"

CEnchantress_energize_01::CEnchantress_energize_01(int _iMode)
: CFollowerState(_iMode)
{
	// StateType
	m_eStateType = STATE_TYPE_ENCHANTRESS_ENERGIZE_01;
}

CEnchantress_energize_01::~CEnchantress_energize_01()
{
}

void CEnchantress_energize_01::Initialize()
{
	// Initialize
	CFollowerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(40);
}

CFollowerState* CEnchantress_energize_01::Action()
{
	return NULL;
}
