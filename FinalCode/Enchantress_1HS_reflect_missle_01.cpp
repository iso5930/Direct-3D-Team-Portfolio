#include "StdAfx.h"
#include "Enchantress_1HS_reflect_missle_01.h"

CEnchantress_1HS_reflect_missle_01::CEnchantress_1HS_reflect_missle_01(int _iMode)
: CFollowerState(_iMode)
{
	// StateType
	m_eStateType = STATE_TYPE_ENCHANTRESS_1HS_REFELECT_MISSLE_01;
}

CEnchantress_1HS_reflect_missle_01::~CEnchantress_1HS_reflect_missle_01()
{
}

void CEnchantress_1HS_reflect_missle_01::Initialize()
{
	// Initialize
	CFollowerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(53);
}

CFollowerState* CEnchantress_1HS_reflect_missle_01::Action()
{
	return NULL;
}
