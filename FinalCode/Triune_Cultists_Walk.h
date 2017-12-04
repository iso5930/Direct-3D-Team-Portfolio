#pragma once
#include "monsterstate.h"

class CTriune_Cultists_Walk :
	public CMonsterState
{
public: 
	virtual void Initialize();
	virtual CMonsterState* Action();

public:
	explicit CTriune_Cultists_Walk(void);
	virtual ~CTriune_Cultists_Walk(void);
};
