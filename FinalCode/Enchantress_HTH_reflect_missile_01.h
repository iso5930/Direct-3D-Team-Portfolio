#pragma once
#include "FollowerState.h"

class CEnchantress_HTH_reflect_missile_01 : public CFollowerState
{
public:
	virtual void Initialize();
	virtual CFollowerState* Action();

public:
	explicit CEnchantress_HTH_reflect_missile_01(int _iMode);
	virtual ~CEnchantress_HTH_reflect_missile_01();
};
