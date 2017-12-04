#pragma once
#include "playerstate.h"

class CBarbarian_Male_DW_Attack_L :	public CPlayerState
{
public:
	virtual void Initialize();
	virtual CPlayerState* Action();

public:
	explicit CBarbarian_Male_DW_Attack_L(void);
	virtual ~CBarbarian_Male_DW_Attack_L(void);
};
