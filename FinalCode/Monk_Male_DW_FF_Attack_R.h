#pragma once
#include "playerstate.h"

class CMonk_Male_DW_FF_Attack_R :	public CPlayerState
{
public:
	virtual void Initialize();
	virtual CPlayerState* Action();

public:
	explicit CMonk_Male_DW_FF_Attack_R(void);
	virtual ~CMonk_Male_DW_FF_Attack_R(void);
};