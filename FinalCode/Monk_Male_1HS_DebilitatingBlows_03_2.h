#pragma once
#include "playerstate.h"

class CMonk_Male_1HS_DebilitatingBlows_03_2 :	public CPlayerState
{
public:
	virtual void Initialize();
	virtual CPlayerState* Action();

public:
	explicit CMonk_Male_1HS_DebilitatingBlows_03_2(void);
	virtual ~CMonk_Male_1HS_DebilitatingBlows_03_2(void);
};
