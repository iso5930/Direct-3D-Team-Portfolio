#pragma once
#include "monsterstate.h"

class CSkeleton_Axe_Red_Death :
	public CMonsterState
{
private:
	bool m_bDeath;

public:
	virtual void Initialize();
	virtual CMonsterState* Action();

public:
	explicit CSkeleton_Axe_Red_Death(void);
	virtual ~CSkeleton_Axe_Red_Death(void);
};
