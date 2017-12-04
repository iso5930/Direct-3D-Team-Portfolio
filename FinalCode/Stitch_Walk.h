#pragma once
#include "monsterstate.h"

class CStitch_Walk :
	public CMonsterState
{
public:
	virtual void Initialize();
	virtual CMonsterState* Action();

public:
	explicit CStitch_Walk(void);
	virtual ~CStitch_Walk(void);
};
