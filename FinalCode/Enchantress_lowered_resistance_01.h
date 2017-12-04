#pragma once
#include "FollowerState.h"

class CEnchantress_lowered_resistance_01 : public CFollowerState
{
public:
	virtual void Initialize();
	virtual CFollowerState* Action();

public:
	explicit CEnchantress_lowered_resistance_01(int _iMode);
	virtual ~CEnchantress_lowered_resistance_01();
};
