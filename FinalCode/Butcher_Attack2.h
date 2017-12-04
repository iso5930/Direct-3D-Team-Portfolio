#pragma once
#include "monsterstate.h"

class CButcher_Attack2 :
	public CMonsterState
{
private:
	// Mode
	int m_iMode;

	// Time
	float m_fTime;

public:
	virtual void Initialize();
	virtual CMonsterState* Action();

private:
	// Mode0
	CMonsterState* Mode0();

	// Mode1
	CMonsterState* Mode1();

public:
	explicit CButcher_Attack2(void);
	virtual ~CButcher_Attack2(void);
};
