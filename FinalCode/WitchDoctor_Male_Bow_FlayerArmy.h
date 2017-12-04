#pragma once
#include "playerstate.h"

class CWitchDoctor_Male_Bow_FlayerArmy :	public CPlayerState
{
public:
	virtual void Initialize();
	virtual CPlayerState* Action();

public:
	explicit CWitchDoctor_Male_Bow_FlayerArmy(void);
	virtual ~CWitchDoctor_Male_Bow_FlayerArmy(void);
};
