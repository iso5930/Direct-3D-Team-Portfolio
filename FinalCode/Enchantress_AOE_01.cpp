#include "StdAfx.h"
#include "Enchantress_AOE_01.h"

CEnchantress_AOE_01::CEnchantress_AOE_01(int _iMode)
: CFollowerState(_iMode)
{
	// StateType
	m_eStateType = STATE_TYPE_ENCHANTRESS_AOE_01;
}

CEnchantress_AOE_01::~CEnchantress_AOE_01()
{
}

void CEnchantress_AOE_01::Initialize()
{
	// Initialize
	CFollowerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(45);
}

CFollowerState* CEnchantress_AOE_01::Action()
{
	return NULL;
}
