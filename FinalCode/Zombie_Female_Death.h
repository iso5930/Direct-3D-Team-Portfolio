#pragma once

#include "MonsterState.h"

class CZombie_Female_Death : public CMonsterState
{
private:
	bool m_bDeath;

public:
	virtual void Initialize();
	virtual CMonsterState* Action();

public:
	explicit CZombie_Female_Death();
	virtual ~CZombie_Female_Death();
};
