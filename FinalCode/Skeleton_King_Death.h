#pragma once
#include "monsterstate.h"

class CSkeleton_King_Death :
	public CMonsterState
{
private:
	bool m_bDeath;
	bool m_bDeathEffect;

public:
	virtual void Initialize();
	virtual CMonsterState* Action();

public:
	explicit CSkeleton_King_Death(void);
	virtual ~CSkeleton_King_Death(void);
};
