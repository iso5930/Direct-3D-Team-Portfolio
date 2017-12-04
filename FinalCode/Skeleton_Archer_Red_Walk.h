#pragma once
#include "monsterstate.h"

class CSkeleton_Archer_Red_Walk :
	public CMonsterState
{
public:
	virtual void Initialize();
	virtual CMonsterState* Action();

public:
	explicit CSkeleton_Archer_Red_Walk(void);
	virtual ~CSkeleton_Archer_Red_Walk(void);
};
