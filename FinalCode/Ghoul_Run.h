#pragma once
#include "monsterstate.h"

class CGhoul_Run :
	public CMonsterState
{
private:
	int m_iMode;

	float m_fTime;
	float m_fChaseTime;

public:
	virtual void Initialize();
	virtual CMonsterState* Action();

private:
	CMonsterState* Mode0();
	CMonsterState* Mode1();
	CMonsterState* Mode2();

public:
	explicit CGhoul_Run(int _iMode);
	virtual ~CGhoul_Run(void);
};