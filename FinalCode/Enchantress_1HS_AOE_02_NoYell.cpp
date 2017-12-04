#include "StdAfx.h"
#include "Enchantress_1HS_AOE_02_NoYell.h"

CEnchantress_1HS_AOE_02_NoYell::CEnchantress_1HS_AOE_02_NoYell(int _iMode)
: CFollowerState(_iMode)
{
	// StateType
	m_eStateType = STATE_TYPE_ENCHANTRESS_1HS_AOE_02_NOYELL;
}

CEnchantress_1HS_AOE_02_NoYell::~CEnchantress_1HS_AOE_02_NoYell()
{
}

void CEnchantress_1HS_AOE_02_NoYell::Initialize()
{
	// Initialize
	CFollowerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(67);
}

CFollowerState* CEnchantress_1HS_AOE_02_NoYell::Action()
{
	return NULL;
}
