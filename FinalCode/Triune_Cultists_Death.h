#pragma once
#include "monsterstate.h"

class CTriune_Cultists_Death :
	public CMonsterState
{
private:
	bool m_bDeath;

public:
	virtual void Initialize();
	virtual CMonsterState* Action();

public:
	explicit CTriune_Cultists_Death(void);
	virtual ~CTriune_Cultists_Death(void);
};
