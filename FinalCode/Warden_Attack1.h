#pragma once
#include "monsterstate.h"

class CWarden_Attack1 :
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
	explicit CWarden_Attack1(void);
	virtual ~CWarden_Attack1(void);
};
