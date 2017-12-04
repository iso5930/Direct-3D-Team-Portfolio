#include "StdAfx.h"
#include "Enchantress_1HS_emote_greet_01.h"

CEnchantress_1HS_emote_greet_01::CEnchantress_1HS_emote_greet_01(int _iMode)
: CFollowerState(_iMode)
{
	// StateType
	m_eStateType = STATE_TYPE_ENCHANTRESS_1HS_EMOTE_GREET_01;
}

CEnchantress_1HS_emote_greet_01::~CEnchantress_1HS_emote_greet_01()
{
}

void CEnchantress_1HS_emote_greet_01::Initialize()
{
	// Initialize
	CFollowerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(64);
}

CFollowerState* CEnchantress_1HS_emote_greet_01::Action()
{
	return NULL;
}
