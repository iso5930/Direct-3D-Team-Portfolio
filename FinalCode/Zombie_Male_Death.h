#pragma once
#include "monsterstate.h"

class CZombie_Male_Death :
	public CMonsterState
{
private:
	bool m_bDeath;

public:
	virtual void Initialize();
	virtual CMonsterState* Action();

public:
	explicit CZombie_Male_Death(void);
	virtual ~CZombie_Male_Death(void);
};
