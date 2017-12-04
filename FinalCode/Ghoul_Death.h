#pragma once
#include "monsterstate.h"

class CGhoul_Death :
	public CMonsterState
{
private:
	bool m_bDeath;

public:
	virtual void Initialize();
	virtual CMonsterState* Action();

public:
	explicit CGhoul_Death(void);
	virtual ~CGhoul_Death(void);
};
