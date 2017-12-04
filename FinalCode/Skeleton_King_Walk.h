#pragma once
#include "monsterstate.h"

class CSkeleton_King_Walk :
	public CMonsterState
{
private:
	int m_iMode;

public:
	virtual void Initialize();
	virtual CMonsterState* Action();

private:
	CMonsterState* Mode0();
	CMonsterState* Mode1();

public:
	explicit CSkeleton_King_Walk(void);
	virtual ~CSkeleton_King_Walk(void);
};
