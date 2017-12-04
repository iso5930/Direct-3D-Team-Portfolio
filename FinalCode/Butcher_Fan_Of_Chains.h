#pragma once
#include "monsterstate.h"

class CButcher_Fan_Of_Chains :
	public CMonsterState
{
public:
	virtual void Initialize();
	virtual CMonsterState* Action();

public:
	explicit CButcher_Fan_Of_Chains(void);
	virtual ~CButcher_Fan_Of_Chains(void);
};
