#pragma once
#include "FollowerState.h"

class CEnchantress_emote_greet_01 : public CFollowerState
{
public:
	virtual void Initialize();
	virtual CFollowerState* Action();

public:
	explicit CEnchantress_emote_greet_01(int _iMode);
	virtual ~CEnchantress_emote_greet_01();
};
