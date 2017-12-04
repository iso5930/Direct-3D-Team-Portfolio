#include "StdAfx.h"
#include "Enchantress_amplify_damage_01.h"

CEnchantress_amplify_damage_01::CEnchantress_amplify_damage_01(int _iMode)
: CFollowerState(_iMode)
{
	// StateType
	m_eStateType = STATE_TYPE_ENCHANTRESS_AMPLIFY_DAMAGE_01;
}

CEnchantress_amplify_damage_01::~CEnchantress_amplify_damage_01()
{
}

void CEnchantress_amplify_damage_01::Initialize()
{
	// Initialize
	CFollowerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(46);
}

CFollowerState* CEnchantress_amplify_damage_01::Action()
{
	return NULL;
}
