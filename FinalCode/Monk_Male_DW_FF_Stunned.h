#pragma once
#include "playerstate.h"

class CMonk_Male_DW_FF_Stunned :	public CPlayerState
{
public:
	virtual void Initialize();
	virtual CPlayerState* Action();

public:
	explicit CMonk_Male_DW_FF_Stunned(void);
	virtual ~CMonk_Male_DW_FF_Stunned(void);
};