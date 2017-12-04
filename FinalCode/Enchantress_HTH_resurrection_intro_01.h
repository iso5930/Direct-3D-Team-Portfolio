#pragma once
#include "FollowerState.h"

class CEnchantress_HTH_resurrection_intro_01 : public CFollowerState
{
public:
	virtual void Initialize();
	virtual CFollowerState* Action();

public:
	explicit CEnchantress_HTH_resurrection_intro_01(int _iMode);
	virtual ~CEnchantress_HTH_resurrection_intro_01();
};
