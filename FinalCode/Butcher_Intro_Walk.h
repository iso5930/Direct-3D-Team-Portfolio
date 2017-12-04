#pragma once
#include "monsterstate.h"

class CButcher_Intro_Walk :
	public CMonsterState
{
public:
	virtual void Initialize();
	virtual CMonsterState* Action();

public:
	explicit CButcher_Intro_Walk(void);
	virtual ~CButcher_Intro_Walk(void);
};
