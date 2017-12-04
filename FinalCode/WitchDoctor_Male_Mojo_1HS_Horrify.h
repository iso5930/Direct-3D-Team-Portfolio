#pragma once
#include "playerstate.h"

class CWitchDoctor_Male_Mojo_1HS_Horrify :	public CPlayerState
{
public:
	virtual void Initialize();
	virtual CPlayerState* Action();

public:
	explicit CWitchDoctor_Male_Mojo_1HS_Horrify(void);
	virtual ~CWitchDoctor_Male_Mojo_1HS_Horrify(void);
};
