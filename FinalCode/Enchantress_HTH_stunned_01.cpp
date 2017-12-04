#include "StdAfx.h"
#include "Enchantress_HTH_stunned_01.h"

CEnchantress_HTH_stunned_01::CEnchantress_HTH_stunned_01(int _iMode)
: CFollowerState(_iMode)
{
	// StateType
	m_eStateType = STATE_TYPE_ENCHANTRESS_HTH_STUNNED_01;
}

CEnchantress_HTH_stunned_01::~CEnchantress_HTH_stunned_01()
{
}

void CEnchantress_HTH_stunned_01::Initialize()
{
	// Initialize
	CFollowerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(17);
}

CFollowerState* CEnchantress_HTH_stunned_01::Action()
{
	return NULL;
}
