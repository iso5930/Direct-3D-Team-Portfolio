#pragma once
#include "monsterstate.h"

class CSkeleton_King_Whirlwind_Start :
	public CMonsterState
{
public:
	virtual void Initialize();
	virtual CMonsterState* Action();

public:
	explicit CSkeleton_King_Whirlwind_Start(void);
	virtual ~CSkeleton_King_Whirlwind_Start(void);
};
