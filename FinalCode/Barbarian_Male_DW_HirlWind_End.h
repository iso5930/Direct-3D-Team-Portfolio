#pragma once
#include "playerstate.h"

class CBarbarian_male_DW_HirlWind_End :	public CPlayerState
{
public:
	virtual void Initialize();
	virtual CPlayerState* Action();

public:
	explicit CBarbarian_male_DW_HirlWind_End(void);
	virtual ~CBarbarian_male_DW_HirlWind_End(void);
};
