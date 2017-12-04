#pragma once
#include "playerstate.h"

class CBarbarian_Male_1HT_Cleave01 :	public CPlayerState
{
public:
	virtual void Initialize();
	virtual CPlayerState* Action();

public:
	explicit CBarbarian_Male_1HT_Cleave01(void);
	virtual ~CBarbarian_Male_1HT_Cleave01(void);
};
