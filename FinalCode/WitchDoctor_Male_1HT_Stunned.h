#pragma once
#include "playerstate.h"

class CWitchDoctor_Male_1HT_Stunned :	public CPlayerState
{
public:
	virtual void Initialize();
	virtual CPlayerState* Action();

public:
	explicit CWitchDoctor_Male_1HT_Stunned(void);
	virtual ~CWitchDoctor_Male_1HT_Stunned(void);
};
