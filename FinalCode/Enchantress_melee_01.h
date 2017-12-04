#pragma once
#include "FollowerState.h"

class CEnchantress_melee_01 : public CFollowerState
{
public:
	virtual void Initialize();
	virtual CFollowerState* Action();

public:
	explicit CEnchantress_melee_01(int _iMode);
	virtual ~CEnchantress_melee_01();
};
