#pragma once
#include "playerstate.h"

class CWitchDoctor_Male_Bow_Attack :	public CPlayerState
{
public:
	virtual void Initialize();
	virtual CPlayerState* Action();

public:
	explicit CWitchDoctor_Male_Bow_Attack(void);
	virtual ~CWitchDoctor_Male_Bow_Attack(void);
};
