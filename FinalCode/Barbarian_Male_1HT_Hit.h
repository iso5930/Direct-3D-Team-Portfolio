#pragma once
#include "playerstate.h"

class CBarbarian_Male_1HT_Hit :	public CPlayerState
{
public:
	virtual void Initialize();
	virtual CPlayerState* Action();

public:
	explicit CBarbarian_Male_1HT_Hit(void);
	virtual ~CBarbarian_Male_1HT_Hit(void);
};