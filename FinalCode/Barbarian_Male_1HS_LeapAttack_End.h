#pragma once
#include "playerstate.h"

class CBarbarian_Male_1HS_LeapAttack_End :	public CPlayerState
{
public:
	virtual void Initialize();
	virtual CPlayerState* Action();

public:
	explicit CBarbarian_Male_1HS_LeapAttack_End(void);
	virtual ~CBarbarian_Male_1HS_LeapAttack_End(void);
};
