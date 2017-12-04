#pragma once
#include "monsterstate.h"

class CButcher_Walk :
	public CMonsterState
{
private:
	float m_fActSelectTime;

public:
	virtual void Initialize();
	virtual CMonsterState* Action();

public:
	explicit CButcher_Walk(void);
	virtual ~CButcher_Walk(void);
};
