#pragma once
#include "FollowerState.h"

class CEnchantress_forceful_push_01 : public CFollowerState
{
public:
	virtual void Initialize();
	virtual CFollowerState* Action();

public:
	explicit CEnchantress_forceful_push_01(int _iMode);
	virtual ~CEnchantress_forceful_push_01();
};
