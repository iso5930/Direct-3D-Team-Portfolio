#pragma once
#include "playerstate.h"

class CMonk_Male_1HS_Hit :	public CPlayerState
{
public:
	virtual void Initialize();
	virtual CPlayerState* Action();

public:
	explicit CMonk_Male_1HS_Hit(void);
	virtual ~CMonk_Male_1HS_Hit(void);
};
