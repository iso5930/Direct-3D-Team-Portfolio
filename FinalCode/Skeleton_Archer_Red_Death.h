#pragma once
#include "monsterstate.h"

class CSkeleton_Archer_Red_Death :
	public CMonsterState
{
private:
	bool m_bDeath;

public:
	virtual void Initialize();
	virtual CMonsterState* Action();

public:
	explicit CSkeleton_Archer_Red_Death(void);
	virtual ~CSkeleton_Archer_Red_Death(void);
};
