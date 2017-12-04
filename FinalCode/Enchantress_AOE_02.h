#pragma once
#include "FollowerState.h"

class CEnchantress_AOE_02 : public CFollowerState
{
public:
	virtual void Initialize();
	virtual CFollowerState* Action();

public:
	explicit CEnchantress_AOE_02(int _iMode);
	virtual ~CEnchantress_AOE_02();
};
