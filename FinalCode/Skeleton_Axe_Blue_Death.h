#pragma once
#include "monsterstate.h"

class CSkeleton_Axe_Blue_Death :
	public CMonsterState
{
private:
	bool m_bDeath;

public:
	virtual void Initialize();
	virtual CMonsterState* Action();

public:
	explicit CSkeleton_Axe_Blue_Death(void);
	virtual ~CSkeleton_Axe_Blue_Death(void);
};
