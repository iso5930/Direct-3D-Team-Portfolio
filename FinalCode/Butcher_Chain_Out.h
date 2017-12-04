#pragma once
#include "monsterstate.h"

class CButcher_Chain_Out :
	public CMonsterState
{
public:
	virtual void Initialize();
	virtual CMonsterState* Action();

public:
	explicit CButcher_Chain_Out(void);
	virtual ~CButcher_Chain_Out(void);
};
