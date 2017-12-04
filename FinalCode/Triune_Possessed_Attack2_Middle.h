#pragma once
#include "monsterstate.h"

class CTriune_Possessed_Attack2_Middle :
	public CMonsterState
{
private:
	float m_fPlayerSearchTime;

public:
	virtual void Initialize();
	virtual CMonsterState* Action();

public:
	explicit CTriune_Possessed_Attack2_Middle(void);
	virtual ~CTriune_Possessed_Attack2_Middle(void);
};
