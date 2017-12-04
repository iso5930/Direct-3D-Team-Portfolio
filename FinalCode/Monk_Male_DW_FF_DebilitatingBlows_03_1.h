#pragma once
#include "playerstate.h"

class CMonk_Male_DW_FF_DebilitatingBlows_03_1 :	public CPlayerState
{
public:
	virtual void Initialize();
	virtual CPlayerState* Action();

public:
	explicit CMonk_Male_DW_FF_DebilitatingBlows_03_1(void);
	virtual ~CMonk_Male_DW_FF_DebilitatingBlows_03_1(void);
};
