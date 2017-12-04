#pragma once
#include "playerstate.h"

class CBarbarian_Male_1HT_Attack :	public CPlayerState
{
public:
	virtual void Initialize();
	virtual CPlayerState* Action();

public:
	explicit CBarbarian_Male_1HT_Attack(void);
	virtual ~CBarbarian_Male_1HT_Attack(void);
};
