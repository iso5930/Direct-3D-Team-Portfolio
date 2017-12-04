#include "StdAfx.h"
#include "Enchantress_emote_greet_01.h"

CEnchantress_emote_greet_01::CEnchantress_emote_greet_01(int _iMode)
: CFollowerState(_iMode)
{
	// StateType
	m_eStateType = STATE_TYPE_ENCHANTRESS_EMOTE_GREET_01;
}

CEnchantress_emote_greet_01::~CEnchantress_emote_greet_01()
{
}

void CEnchantress_emote_greet_01::Initialize()
{
	// Initialize
	CFollowerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(41);
}

CFollowerState* CEnchantress_emote_greet_01::Action()
{
	return NULL;
}
