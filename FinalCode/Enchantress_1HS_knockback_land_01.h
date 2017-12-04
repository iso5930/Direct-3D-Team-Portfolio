#pragma once
#include "FollowerState.h"

class CEnchantress_1HS_knockback_land_01 : public CFollowerState
{
public:
	virtual void Initialize();
	virtual CFollowerState* Action();

public:
	explicit CEnchantress_1HS_knockback_land_01(int _iMode);
	virtual ~CEnchantress_1HS_knockback_land_01();
};
