#pragma once
#include "monsterstate.h"

class CWarden_Death :
	public CMonsterState
{
private:
	bool m_bDeath;

public:
	virtual void Initialize();
	virtual CMonsterState* Action();

public:
	explicit CWarden_Death(void);
	virtual ~CWarden_Death(void);
};
