#pragma once
#include "monsterstate.h"

class CTriune_Possessed_Hit :
	public CMonsterState
{
public:
	virtual void Initialize();
	virtual CMonsterState* Action();

public:
	explicit CTriune_Possessed_Hit(void);
	virtual ~CTriune_Possessed_Hit(void);
};
