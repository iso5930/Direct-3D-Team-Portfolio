#pragma once
#include "monsterstate.h"

class CWarden_Hit :
	public CMonsterState
{
public:
	virtual void Initialize();
	virtual CMonsterState* Action();

public:
	explicit CWarden_Hit(void);
	virtual ~CWarden_Hit(void);
};
