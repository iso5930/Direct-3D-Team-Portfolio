#pragma once
#include "playerstate.h"

class CWitchDoctor_Male_Mojo_1HS_Soul_Harvest :	public CPlayerState
{
public:
	virtual void Initialize();
	virtual CPlayerState* Action();

public:
	explicit CWitchDoctor_Male_Mojo_1HS_Soul_Harvest(void);
	virtual ~CWitchDoctor_Male_Mojo_1HS_Soul_Harvest(void);
};