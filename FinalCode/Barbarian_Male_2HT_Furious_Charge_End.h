#pragma once
#include "playerstate.h"

class CBarbarian_Male_2HT_Furious_Charge_End :	public CPlayerState
{
public:
	virtual void Initialize();
	virtual CPlayerState* Action();

public:
	explicit CBarbarian_Male_2HT_Furious_Charge_End(void);
	virtual ~CBarbarian_Male_2HT_Furious_Charge_End(void);
};
