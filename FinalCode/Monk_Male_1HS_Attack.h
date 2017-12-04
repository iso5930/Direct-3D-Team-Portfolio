#pragma once
#include "playerstate.h"

class CMonk_Male_1HS_Attack :	public CPlayerState
{
public:
	virtual void Initialize();
	virtual CPlayerState* Action();

public:
	explicit CMonk_Male_1HS_Attack(void);
	virtual ~CMonk_Male_1HS_Attack(void);
};
