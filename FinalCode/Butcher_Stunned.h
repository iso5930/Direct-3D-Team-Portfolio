#pragma once
#include "monsterstate.h"

class CButcher_Stunned :
	public CMonsterState
{
public:
	virtual void Initialize();
	virtual CMonsterState* Action();

public:
	explicit CButcher_Stunned(void);
	virtual ~CButcher_Stunned(void);
};
