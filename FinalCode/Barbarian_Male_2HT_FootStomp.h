#pragma once
#include "playerstate.h"

class CBarbarian_Male_2HT_FootStomp :	public CPlayerState
{
public:
	virtual void Initialize();
	virtual CPlayerState* Action();

public:
	explicit CBarbarian_Male_2HT_FootStomp(void);
	virtual ~CBarbarian_Male_2HT_FootStomp(void);
};
