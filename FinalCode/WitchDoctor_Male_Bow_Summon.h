#pragma once
#include "playerstate.h"

class CWitchDoctor_Male_Bow_Summon :	public CPlayerState
{
public:
	virtual void Initialize();
	virtual CPlayerState* Action();

public:
	explicit CWitchDoctor_Male_Bow_Summon(void);
	virtual ~CWitchDoctor_Male_Bow_Summon(void);
};
