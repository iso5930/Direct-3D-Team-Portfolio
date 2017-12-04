#pragma once
#include "monsterstate.h"

class CSkeleton_King_Teleport :
	public CMonsterState
{
private:
	float m_fInvisibleTime;
	bool m_bEffect;

public:
	virtual void Initialize();
	virtual CMonsterState* Action();

public:
	explicit CSkeleton_King_Teleport(void);
	virtual ~CSkeleton_King_Teleport(void);
};
