#pragma once
#include "MonsterState.h"

class CZombie_Skinny_Male_Red_Death : public CMonsterState
{
private:
	bool m_bDeath;

public:
	virtual void Initialize();
	virtual CMonsterState* Action();

public:
	explicit CZombie_Skinny_Male_Red_Death(void);
	virtual ~CZombie_Skinny_Male_Red_Death(void);
};
