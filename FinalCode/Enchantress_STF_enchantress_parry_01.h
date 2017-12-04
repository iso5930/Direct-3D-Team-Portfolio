#pragma once
#include "FollowerState.h"

class CEnchantress_STF_enchantress_parry_01 : public CFollowerState
{
public:
	virtual void Initialize();
	virtual CFollowerState* Action();

public:
	explicit CEnchantress_STF_enchantress_parry_01(int _iMode);
	virtual ~CEnchantress_STF_enchantress_parry_01();
};
