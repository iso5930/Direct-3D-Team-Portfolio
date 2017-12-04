#pragma once
#include "monsterstate.h"

class CSkeleton_King_Intro :
	public CMonsterState
{
public:
	virtual void Initialize();
	virtual CMonsterState* Action();

public:
	explicit CSkeleton_King_Intro(void);
	virtual ~CSkeleton_King_Intro(void);
};
