#pragma once
#include "playerstate.h"

class CWitchDoctor_Male_STF_Hit :	public CPlayerState
{
public:
	virtual void Initialize();
	virtual CPlayerState* Action();

public:
	explicit CWitchDoctor_Male_STF_Hit(void);
	virtual ~CWitchDoctor_Male_STF_Hit(void);
};
