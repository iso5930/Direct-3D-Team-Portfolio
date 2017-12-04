#pragma once
#include "monsterstate.h"

class CWarden_Attack2 :
	public CMonsterState
{
private:
	bool m_bEffect;

public:
	virtual void Initialize();
	virtual CMonsterState* Action();

public:
	explicit CWarden_Attack2(void);
	virtual ~CWarden_Attack2(void);
};
