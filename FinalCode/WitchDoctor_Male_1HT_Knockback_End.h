#pragma once
#include "playerstate.h"

class CWitchDoctor_Male_1HT_Knockback_End :	public CPlayerState
{
public:
	virtual void Initialize();
	virtual CPlayerState* Action();

public:
	explicit CWitchDoctor_Male_1HT_Knockback_End(void);
	virtual ~CWitchDoctor_Male_1HT_Knockback_End(void);
};
