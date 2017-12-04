#pragma once
#include "monsterstate.h"

class CSkeleton_King_Taunt :
	public CMonsterState
{
public:
	virtual void Initialize();
	virtual CMonsterState* Action();

public:
	explicit CSkeleton_King_Taunt(void);
	virtual ~CSkeleton_King_Taunt(void);
};
