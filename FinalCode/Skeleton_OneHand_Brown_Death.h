#pragma once
#include "monsterstate.h"

class CSkeleton_OneHand_Brown_Death :
	public CMonsterState
{
private:
	bool m_bDeath;

public:
	virtual void Initialize();
	virtual CMonsterState* Action();

public:
	explicit CSkeleton_OneHand_Brown_Death(void);
	virtual ~CSkeleton_OneHand_Brown_Death(void);
};
