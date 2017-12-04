#include "StdAfx.h"
#include "Enchantress_1HS_amplify_damage_01.h"

CEnchantress_1HS_amplify_damage_01::CEnchantress_1HS_amplify_damage_01(int _iMode)
: CFollowerState(_iMode)
{
	// StateType
	m_eStateType = STATE_TYPE_ENCHANTRESS_1HS_AMPLIFY_DAMAGE_01;
}

CEnchantress_1HS_amplify_damage_01::~CEnchantress_1HS_amplify_damage_01()
{
}

void CEnchantress_1HS_amplify_damage_01::Initialize()
{
	// Initialize
	CFollowerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(70);
}

CFollowerState* CEnchantress_1HS_amplify_damage_01::Action()
{
	return NULL;
}
