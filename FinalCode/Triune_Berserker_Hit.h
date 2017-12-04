#pragma once
#include "monsterstate.h"

class CTriune_Berserker_Hit :
	public CMonsterState
{
public:
	virtual void Initialize();
	virtual CMonsterState* Action();

public:
	explicit CTriune_Berserker_Hit(void);
	virtual ~CTriune_Berserker_Hit(void);
};
