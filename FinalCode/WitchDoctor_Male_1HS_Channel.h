#pragma once
#include "playerstate.h"

class CWitchDoctor_Male_1HS_Channel :	public CPlayerState
{
public:
	virtual void Initialize();
	virtual CPlayerState* Action();

public:
	explicit CWitchDoctor_Male_1HS_Channel();
	virtual ~CWitchDoctor_Male_1HS_Channel(void);
};
