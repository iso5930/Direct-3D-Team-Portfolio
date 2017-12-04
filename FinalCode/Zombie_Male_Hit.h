#pragma once
#include "monsterstate.h"

class CZombie_Male_Hit :
	public CMonsterState
{
public:
	virtual void Initialize();
	virtual CMonsterState* Action();

public:
	explicit CZombie_Male_Hit(void);
	virtual ~CZombie_Male_Hit(void);
};
