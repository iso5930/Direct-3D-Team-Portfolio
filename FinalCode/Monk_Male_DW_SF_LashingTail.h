#pragma once
#include "playerstate.h"

class CMonk_Male_DW_SF_LashingTail :	public CPlayerState
{
public:
	virtual void Initialize();
	virtual CPlayerState* Action();

public:
	explicit CMonk_Male_DW_SF_LashingTail(void);
	virtual ~CMonk_Male_DW_SF_LashingTail(void);
};
