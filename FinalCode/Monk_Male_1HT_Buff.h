#pragma once
#include "playerstate.h"

class CMonk_Male_1HT_Buff :	public CPlayerState
{
public:
	virtual void Initialize();
	virtual CPlayerState* Action();

public:
	explicit CMonk_Male_1HT_Buff(void);
	virtual ~CMonk_Male_1HT_Buff(void);
};
