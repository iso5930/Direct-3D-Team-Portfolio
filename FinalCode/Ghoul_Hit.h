#pragma once
#include "monsterstate.h"

class CGhoul_Hit :
	public CMonsterState
{
public:
	virtual void Initialize();
	virtual CMonsterState* Action();

public:
	explicit CGhoul_Hit(void);
	virtual ~CGhoul_Hit(void);
};
