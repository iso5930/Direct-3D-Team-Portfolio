#pragma once
#include "monsterstate.h"

class CSkeleton_King_Intro_Idle :
	public CMonsterState
{
public:
	virtual void Initialize();
	virtual CMonsterState* Action();

public:
	explicit CSkeleton_King_Intro_Idle(void);
	virtual ~CSkeleton_King_Intro_Idle(void);
};
