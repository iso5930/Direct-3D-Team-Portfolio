#pragma once
#include "playerstate.h"

class CMonk_Male_STF_Stunned :	public CPlayerState
{
public:
	virtual void Initialize();
	virtual CPlayerState* Action();

public:
	explicit CMonk_Male_STF_Stunned(void);
	virtual ~CMonk_Male_STF_Stunned(void);
};
