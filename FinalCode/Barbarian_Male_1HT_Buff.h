#pragma once
#include "playerstate.h"

class CBarbarian_Male_1HT_Buff :	public CPlayerState
{
public:
	virtual void Initialize();
	virtual CPlayerState* Action();

public:
	explicit CBarbarian_Male_1HT_Buff(void);
	virtual ~CBarbarian_Male_1HT_Buff(void);
};
