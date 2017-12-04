#pragma once
#include "monsterstate.h"

class CButcher_Pull_Attack :
	public CMonsterState
{
public:
	virtual void Initialize();
	virtual CMonsterState* Action();

public:
	explicit CButcher_Pull_Attack(void);
	virtual ~CButcher_Pull_Attack(void);
};
