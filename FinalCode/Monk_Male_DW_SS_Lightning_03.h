#pragma once
#include "playerstate.h"

class CMonk_Male_DW_SS_Lightning_03 :	public CPlayerState
{
public:
	virtual void Initialize();
	virtual CPlayerState* Action();

public:
	explicit CMonk_Male_DW_SS_Lightning_03(void);
	virtual ~CMonk_Male_DW_SS_Lightning_03(void);
};