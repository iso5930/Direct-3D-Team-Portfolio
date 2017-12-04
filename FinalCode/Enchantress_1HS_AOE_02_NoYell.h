#pragma once
#include "FollowerState.h"

class CEnchantress_1HS_AOE_02_NoYell : public CFollowerState
{
public:
	virtual void Initialize();
	virtual CFollowerState* Action();

public:
	explicit CEnchantress_1HS_AOE_02_NoYell(int _iMode);
	virtual ~CEnchantress_1HS_AOE_02_NoYell();
};
