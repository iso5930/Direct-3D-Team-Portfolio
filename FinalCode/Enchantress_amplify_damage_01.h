#pragma once
#include "FollowerState.h"

class CEnchantress_amplify_damage_01 : public CFollowerState
{
public:
	virtual void Initialize();
	virtual CFollowerState* Action();

public:
	explicit CEnchantress_amplify_damage_01(int _iMode);
	virtual ~CEnchantress_amplify_damage_01();
};
