#pragma once
#include "monsterstate.h"

class CButcher_Idle :
	public CMonsterState
{
private:
	float m_fActTime;

public:
	virtual void Initialize();
	virtual CMonsterState* Action();

public:
	explicit CButcher_Idle(void);
	virtual ~CButcher_Idle(void);
};
