#pragma once
#include "monsterstate.h"

class CTriune_Berserker_Death :
	public CMonsterState
{
private:
	bool m_bDeath;

public:
	virtual void Initialize();
	virtual CMonsterState* Action();

public:
	explicit CTriune_Berserker_Death(void);
	virtual ~CTriune_Berserker_Death(void);
};
