#pragma once
#include "playerstate.h"

class CWitchDoctor_Male_Bow_FastCast :	public CPlayerState
{
public:
	virtual void Initialize();
	virtual CPlayerState* Action();

public:
	explicit CWitchDoctor_Male_Bow_FastCast(void);
	virtual ~CWitchDoctor_Male_Bow_FastCast(void);
};
