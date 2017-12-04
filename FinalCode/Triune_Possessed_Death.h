#pragma once
#include "monsterstate.h"

class CTriune_Possessed_Death :
	public CMonsterState
{
private:
	bool m_bDeath;

public:
	virtual void Initialize();
	virtual CMonsterState* Action();

public:
	explicit CTriune_Possessed_Death(void);
	virtual ~CTriune_Possessed_Death(void);
};
