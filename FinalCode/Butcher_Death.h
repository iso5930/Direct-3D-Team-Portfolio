#pragma once
#include "monsterstate.h"

class CButcher_Death :
	public CMonsterState
{
public:
	virtual void Initialize();
	virtual CMonsterState* Action();

public:
	explicit CButcher_Death(void);
	virtual ~CButcher_Death(void);
};
