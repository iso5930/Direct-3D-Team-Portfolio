#pragma once
#include "playerstate.h"

class CMonk_Male_2HT_Attack :	public CPlayerState
{
public:
	virtual void Initialize();
	virtual CPlayerState* Action();

public:
	explicit CMonk_Male_2HT_Attack(void);
	virtual ~CMonk_Male_2HT_Attack(void);
};
