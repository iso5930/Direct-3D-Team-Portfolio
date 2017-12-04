#pragma once
#include "monsterstate.h"

class CSkeleton_King_Teleport_Back_Pose :
	public CMonsterState
{
private:
	D3DXVECTOR3 m_vMovePos;

public:
	virtual void Initialize();
	virtual CMonsterState* Action();

public:
	explicit CSkeleton_King_Teleport_Back_Pose(void);
	virtual ~CSkeleton_King_Teleport_Back_Pose(void);
};
