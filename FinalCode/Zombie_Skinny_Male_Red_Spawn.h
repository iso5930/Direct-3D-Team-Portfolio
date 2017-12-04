#pragma once
#include "monsterstate.h"

class CZombie_Skinny_Male_Red_Spawn :
	public CMonsterState
{
public:
	virtual void Initialize();
	virtual CMonsterState* Action();

public:
	explicit CZombie_Skinny_Male_Red_Spawn(void);
	virtual ~CZombie_Skinny_Male_Red_Spawn(void);
};
