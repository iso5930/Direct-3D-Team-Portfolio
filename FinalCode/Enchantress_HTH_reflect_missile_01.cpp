#include "StdAfx.h"
#include "Enchantress_HTH_reflect_missile_01.h"

CEnchantress_HTH_reflect_missile_01::CEnchantress_HTH_reflect_missile_01(int _iMode)
: CFollowerState(_iMode)
{
	// StateType
	m_eStateType = STATE_TYPE_ENCHANTRESS_HTH_REFLECT_MISSILE_01;
}

CEnchantress_HTH_reflect_missile_01::~CEnchantress_HTH_reflect_missile_01()
{
}

void CEnchantress_HTH_reflect_missile_01::Initialize()
{
	// Initialize
	CFollowerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(22);
}

CFollowerState* CEnchantress_HTH_reflect_missile_01::Action()
{
	return NULL;
}
