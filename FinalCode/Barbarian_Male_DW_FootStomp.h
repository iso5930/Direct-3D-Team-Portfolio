#pragma once
#include "playerstate.h"

class CBarbarian_Male_DW_FootStomp :	public CPlayerState
{
public:
	virtual void Initialize();
	virtual CPlayerState* Action();

public:
	explicit CBarbarian_Male_DW_FootStomp(void);
	virtual ~CBarbarian_Male_DW_FootStomp(void);
};
