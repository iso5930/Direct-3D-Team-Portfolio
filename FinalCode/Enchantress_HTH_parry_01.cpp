#include "StdAfx.h"
#include "Enchantress_HTH_parry_01.h"

CEnchantress_HTH_parry_01::CEnchantress_HTH_parry_01(int _iMode)
: CFollowerState(_iMode)
{
	// StateType
	m_eStateType = STATE_TYPE_ENCHANTRESS_HTH_PARRY_01;
}

CEnchantress_HTH_parry_01::~CEnchantress_HTH_parry_01()
{
}

void CEnchantress_HTH_parry_01::Initialize()
{
	// Initialize
	CFollowerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(23);
}

CFollowerState* CEnchantress_HTH_parry_01::Action()
{
	return NULL;
}
