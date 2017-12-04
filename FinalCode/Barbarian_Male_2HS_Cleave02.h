#pragma once
#include "playerstate.h"

class CBarbarian_Male_2HS_Cleave02 :	public CPlayerState
{
public:
	virtual void Initialize();
	virtual CPlayerState* Action();

public:
	explicit CBarbarian_Male_2HS_Cleave02(void);
	virtual ~CBarbarian_Male_2HS_Cleave02(void);
};
