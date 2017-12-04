#include "StdAfx.h"
#include "Enchantress_HTH_AOE_02.h"

CEnchantress_HTH_AOE_02::CEnchantress_HTH_AOE_02(int _iMode)
: CFollowerState(_iMode)
{
	// StateType
	m_eStateType = STATE_TYPE_ENCHANTRESS_HTH_AOE_02;
}

CEnchantress_HTH_AOE_02::~CEnchantress_HTH_AOE_02()
{
}

void CEnchantress_HTH_AOE_02::Initialize()
{
	// Initialize
	CFollowerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(34);
}

CFollowerState* CEnchantress_HTH_AOE_02::Action()
{
	return NULL;
}
