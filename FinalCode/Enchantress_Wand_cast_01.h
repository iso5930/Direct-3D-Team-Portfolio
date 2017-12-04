#pragma once
#include "FollowerState.h"

class CEnchantress_Wand_cast_01 : public CFollowerState
{
public:
	virtual void Initialize();
	virtual CFollowerState* Action();

public:
	explicit CEnchantress_Wand_cast_01(int _iMode);
	virtual ~CEnchantress_Wand_cast_01();
};
