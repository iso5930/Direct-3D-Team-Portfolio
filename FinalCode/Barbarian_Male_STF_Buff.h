#pragma once
#include "playerstate.h"

class CBarbarian_Male_STF_Buff :	public CPlayerState
{
public:
	virtual void Initialize();
	virtual CPlayerState* Action();

public:
	explicit CBarbarian_Male_STF_Buff(void);
	virtual ~CBarbarian_Male_STF_Buff(void);
};
