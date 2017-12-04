#include "StdAfx.h"
#include "Enchantress_cast_01.h"

CEnchantress_cast_01::CEnchantress_cast_01(int _iMode)
: CFollowerState(_iMode)
{
	// StateType
	m_eStateType = STATE_TYPE_ENCHANTRESS_CAST_01;
}

CEnchantress_cast_01::~CEnchantress_cast_01()
{
}

void CEnchantress_cast_01::Initialize()
{
	// Initialize
	CFollowerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(42);
}

CFollowerState* CEnchantress_cast_01::Action()
{
	return NULL;
}
