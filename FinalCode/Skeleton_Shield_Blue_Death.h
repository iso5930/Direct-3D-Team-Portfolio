#pragma once
#include "monsterstate.h"

class CSkeleton_Shield_Blue_Death :
	public CMonsterState
{
private:
	bool m_bDeath;

public:
	virtual void Initialize();
	virtual CMonsterState* Action();

public:
	CSkeleton_Shield_Blue_Death(void);
	~CSkeleton_Shield_Blue_Death(void);
};
