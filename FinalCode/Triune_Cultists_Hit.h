#pragma once
#include "monsterstate.h"

class CTriune_Cultists_Hit :
	public CMonsterState
{
public:
	virtual void Initialize();
	virtual CMonsterState* Action();

public:
	explicit CTriune_Cultists_Hit(void);
	virtual ~CTriune_Cultists_Hit(void);
};
