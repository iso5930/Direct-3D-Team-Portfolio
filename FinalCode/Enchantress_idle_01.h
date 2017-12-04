#pragma once
#include "FollowerState.h"

class CEnchantress_idle_01 : public CFollowerState
{
public:
	virtual void Initialize();
	virtual CFollowerState* Action();

public:
	explicit CEnchantress_idle_01(int _iMode);
	virtual ~CEnchantress_idle_01();
};
