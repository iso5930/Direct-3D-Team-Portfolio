#pragma once
#include "playerstate.h"

class CWitchDoctor_Male_XBow_Summon_Charger :	public CPlayerState
{
public:
	virtual void Initialize();
	virtual CPlayerState* Action();

public:
	explicit CWitchDoctor_Male_XBow_Summon_Charger(void);
	virtual ~CWitchDoctor_Male_XBow_Summon_Charger(void);
};