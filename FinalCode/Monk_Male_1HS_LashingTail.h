#pragma once
#include "playerstate.h"

class CMonk_Male_1HS_LashingTail :	public CPlayerState
{
public:
	virtual void Initialize();
	virtual CPlayerState* Action();

public:
	explicit CMonk_Male_1HS_LashingTail(void);
	virtual ~CMonk_Male_1HS_LashingTail(void);
};