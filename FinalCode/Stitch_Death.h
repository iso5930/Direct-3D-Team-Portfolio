#pragma once
#include "monsterstate.h"

class CStitch_Death :
	public CMonsterState
{
private:
	bool m_bDeath;

public:
	virtual void Initialize();
	virtual CMonsterState* Action();

public:
	explicit CStitch_Death(void);
	virtual ~CStitch_Death(void);
};
