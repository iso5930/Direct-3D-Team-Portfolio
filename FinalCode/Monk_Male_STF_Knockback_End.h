#pragma once
#include "playerstate.h"

class CMonk_Male_STF_Knockback_End :	public CPlayerState
{
public:
	virtual void Initialize();
	virtual CPlayerState* Action();

public:
	explicit CMonk_Male_STF_Knockback_End(void);
	virtual ~CMonk_Male_STF_Knockback_End(void);
};
