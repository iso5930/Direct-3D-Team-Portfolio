#pragma once
#include "monsterstate.h"

class CStitch_Hit :
	public CMonsterState
{
public:
	virtual void Initialize();
	virtual CMonsterState* Action();

public:
	explicit CStitch_Hit(void);
	virtual ~CStitch_Hit(void);
};
