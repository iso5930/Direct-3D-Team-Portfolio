#pragma once
#include "monsterstate.h"

class CSkeleton_Shield_Blue_Spawn :
	public CMonsterState
{
public:
	virtual void Initialize();
	virtual CMonsterState* Action();

public:
	explicit CSkeleton_Shield_Blue_Spawn(void);
	virtual ~CSkeleton_Shield_Blue_Spawn(void);
};
