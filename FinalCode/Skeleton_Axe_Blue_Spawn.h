#pragma once
#include "monsterstate.h"

class CSkeleton_Axe_Blue_Spawn :
	public CMonsterState
{
public:
	virtual void Initialize();
	virtual CMonsterState* Action();

public:
	explicit CSkeleton_Axe_Blue_Spawn(void);
	virtual ~CSkeleton_Axe_Blue_Spawn(void);
};
