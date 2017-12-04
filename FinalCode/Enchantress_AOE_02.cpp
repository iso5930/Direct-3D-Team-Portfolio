#include "StdAfx.h"
#include "Enchantress_AOE_02.h"

CEnchantress_AOE_02::CEnchantress_AOE_02(int _iMode)
: CFollowerState(_iMode)
{
	// StateType
	m_eStateType = STATE_TYPE_ENCHANTRESS_AOE_02;
}

CEnchantress_AOE_02::~CEnchantress_AOE_02()
{
}

void CEnchantress_AOE_02::Initialize()
{
	// Initialize
	CFollowerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(44);
}

CFollowerState* CEnchantress_AOE_02::Action()
{
	return NULL;
}
