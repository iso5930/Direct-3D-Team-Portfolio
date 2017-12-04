#pragma once
#include "FollowerState.h"

class CEnchantress_1HS_run_01 : public CFollowerState
{
public:
	virtual void Initialize();
	virtual CFollowerState* Action();

private:
	// Mode0 - ToWait
	CFollowerState* Mode0();

public:
	explicit CEnchantress_1HS_run_01(int _iMode);
	virtual ~CEnchantress_1HS_run_01();
};
