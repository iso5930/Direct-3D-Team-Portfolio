#pragma once
#include "monsterstate.h"

class CButcher_Chain_In :
	public CMonsterState
{
public:
	virtual void Initialize();
	virtual CMonsterState* Action();

public:
	explicit CButcher_Chain_In(void);
	virtual ~CButcher_Chain_In(void);
};
