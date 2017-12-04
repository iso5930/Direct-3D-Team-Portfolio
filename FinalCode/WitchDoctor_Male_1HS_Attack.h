#pragma once
#include "playerstate.h"

class CWitchDoctor_Male_1HS_Attack :	public CPlayerState
{
public:
	virtual void Initialize();
	virtual CPlayerState* Action();

public:
	explicit CWitchDoctor_Male_1HS_Attack(void);
	virtual ~CWitchDoctor_Male_1HS_Attack(void);
};
