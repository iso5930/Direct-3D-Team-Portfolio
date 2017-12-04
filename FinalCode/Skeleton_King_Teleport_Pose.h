#pragma once
#include "monsterstate.h"

class CSkeleton_King_Teleport_Pose :
	public CMonsterState
{
public:
	virtual void Initialize();
	virtual CMonsterState* Action();

public:
	explicit CSkeleton_King_Teleport_Pose(void);
	virtual ~CSkeleton_King_Teleport_Pose(void);
};
