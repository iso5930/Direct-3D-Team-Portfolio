#pragma once
#include "MonsterState.h"

class CZombie_Skinny_Male_Red_Hit : public CMonsterState
{
public:
	virtual void Initialize();
	virtual CMonsterState* Action();

public:
	explicit CZombie_Skinny_Male_Red_Hit(void);
	virtual ~CZombie_Skinny_Male_Red_Hit(void);
};
