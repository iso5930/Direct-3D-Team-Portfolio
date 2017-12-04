#pragma once
#include "monsterstate.h"

class CTriune_Vessel_Activation :
	public CMonsterState
{
public:
	virtual void Initialize();
	virtual CMonsterState* Action();

public:
	explicit CTriune_Vessel_Activation(void);
	virtual ~CTriune_Vessel_Activation(void);
};
