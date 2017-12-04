#pragma once
#include "FollowerState.h"

class CEnchantress_run_01 : public CFollowerState
{
public:
	virtual void Initialize();
	virtual CFollowerState* Action();

public:
	explicit CEnchantress_run_01(int _iMode);
	virtual ~CEnchantress_run_01();
};
