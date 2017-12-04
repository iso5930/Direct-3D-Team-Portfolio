#include "StdAfx.h"
#include "Enchantress_stunned_01.h"

CEnchantress_stunned_01::CEnchantress_stunned_01(int _iMode)
: CFollowerState(_iMode)
{
	// StateType
	m_eStateType = STATE_TYPE_ENCHANTRESS_STUNNED_01;
}

CEnchantress_stunned_01::~CEnchantress_stunned_01()
{
}

void CEnchantress_stunned_01::Initialize()
{
	// Initialize
	CFollowerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(2);
}

CFollowerState* CEnchantress_stunned_01::Action()
{
	return NULL;
}
