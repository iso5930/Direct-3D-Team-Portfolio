#pragma once
#include "FollowerState.h"

class CEnchantress_get_hit_01 : public CFollowerState
{
public:
	virtual void Initialize();
	virtual CFollowerState* Action();

public:
	explicit CEnchantress_get_hit_01(int _iMode);
	virtual ~CEnchantress_get_hit_01();
};
