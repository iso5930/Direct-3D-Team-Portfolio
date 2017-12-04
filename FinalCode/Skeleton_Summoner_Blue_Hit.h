#pragma once
#include "monsterstate.h"

class CSkeleton_Summoner_Blue_Hit :
	public CMonsterState
{
public:
	virtual void Initialize();
	virtual CMonsterState* Action();

public:
	explicit CSkeleton_Summoner_Blue_Hit(void);
	virtual ~CSkeleton_Summoner_Blue_Hit(void);
};
