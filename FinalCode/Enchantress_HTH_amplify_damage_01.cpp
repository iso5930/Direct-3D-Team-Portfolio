#include "StdAfx.h"
#include "Enchantress_HTH_amplify_damage_01.h"

CEnchantress_HTH_amplify_damage_01::CEnchantress_HTH_amplify_damage_01(int _iMode)
: CFollowerState(_iMode)
{
	// StateType
	m_eStateType = STATE_TYPE_ENCHANTRESS_HTH_AMPLIFY_DAMAGE_01;
}

CEnchantress_HTH_amplify_damage_01::~CEnchantress_HTH_amplify_damage_01()
{
}

void CEnchantress_HTH_amplify_damage_01::Initialize()
{
	// Initialize
	CFollowerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(36);
}

CFollowerState* CEnchantress_HTH_amplify_damage_01::Action()
{
	return NULL;
}
