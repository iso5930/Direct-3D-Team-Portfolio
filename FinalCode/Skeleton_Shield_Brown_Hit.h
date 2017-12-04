#pragma once
#include "MonsterState.h"

class CSkeleton_Shield_Brown_Hit :
	public CMonsterState
{
public:
	virtual void Initialize();
	virtual CMonsterState* Action();

public:
	CSkeleton_Shield_Brown_Hit(void);
	virtual ~CSkeleton_Shield_Brown_Hit(void);
};
