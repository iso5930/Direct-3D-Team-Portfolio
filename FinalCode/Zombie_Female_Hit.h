#pragma once

#include "MonsterState.h"

class CZombie_Female_Hit : public CMonsterState
{
public:
	virtual void Initialize();
	virtual CMonsterState* Action();

public:
	explicit CZombie_Female_Hit();
	virtual ~CZombie_Female_Hit();
};
