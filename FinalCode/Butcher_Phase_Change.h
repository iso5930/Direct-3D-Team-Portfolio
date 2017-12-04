#pragma once
#include "monsterstate.h"

class CButcher_Phase_Change :
	public CMonsterState
{
public:
	virtual void Initialize();
	virtual CMonsterState* Action();

public:
	explicit CButcher_Phase_Change(void);
	virtual ~CButcher_Phase_Change(void);
};
