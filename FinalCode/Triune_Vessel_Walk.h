#pragma once
#include "monsterstate.h"

class CTriune_Vessel_Walk :
	public CMonsterState
{
public:
	virtual void Initialize();
	virtual CMonsterState* Action();

public:
	explicit CTriune_Vessel_Walk(void);
	virtual ~CTriune_Vessel_Walk(void);
};
