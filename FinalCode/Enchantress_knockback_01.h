#pragma once
#include "FollowerState.h"

class CEnchantress_knockback_01 : public CFollowerState
{
public:
	virtual void Initialize();
	virtual CFollowerState* Action();

public:
	explicit CEnchantress_knockback_01(int _iMode);
	virtual ~CEnchantress_knockback_01();
};
