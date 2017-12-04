#pragma once
#include "monsterstate.h"

class CButcher_Intro :
	public CMonsterState
{
public:
	virtual void Initialize();
	virtual CMonsterState* Action();

public:
	explicit CButcher_Intro(void);
	virtual	~CButcher_Intro(void);
};
