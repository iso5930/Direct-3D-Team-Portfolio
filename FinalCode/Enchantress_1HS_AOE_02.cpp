#include "StdAfx.h"
#include "Enchantress_1HS_AOE_02.h"

CEnchantress_1HS_AOE_02::CEnchantress_1HS_AOE_02(int _iMode)
: CFollowerState(_iMode)
{
	// StateType
	m_eStateType = STATE_TYPE_ENCHANTRESS_1HS_AOE_02;
}

CEnchantress_1HS_AOE_02::~CEnchantress_1HS_AOE_02()
{
}

void CEnchantress_1HS_AOE_02::Initialize()
{
	// Initialize
	CFollowerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(68);
}

CFollowerState* CEnchantress_1HS_AOE_02::Action()
{
	return NULL;
}
