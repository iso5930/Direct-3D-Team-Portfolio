#pragma once
#include "FollowerState.h"

class CEnchantress_energy_bomb_01 : public CFollowerState
{
public:
	virtual void Initialize();
	virtual CFollowerState* Action();

public:
	explicit CEnchantress_energy_bomb_01(int _iMode);
	virtual ~CEnchantress_energy_bomb_01();
};
