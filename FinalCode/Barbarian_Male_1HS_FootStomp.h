#pragma once
#include "playerstate.h"

class CBarbarian_Male_1HS_FootStomp :	public CPlayerState
{
public:
	virtual void Initialize();
	virtual CPlayerState* Action();

public:
	explicit CBarbarian_Male_1HS_FootStomp(void);
	virtual ~CBarbarian_Male_1HS_FootStomp(void);
};
