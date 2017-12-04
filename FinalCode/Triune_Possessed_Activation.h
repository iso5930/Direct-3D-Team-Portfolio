#pragma once
#include "monsterstate.h"

class CTriune_Possessed_Activation :
	public CMonsterState
{
private:
	bool m_bEffect;
	float m_fInvisibleTime;
	bool m_bInvisibleCheck;

public:
	virtual void Initialize();
	virtual CMonsterState* Action();

public:
	explicit CTriune_Possessed_Activation(void);
	virtual ~CTriune_Possessed_Activation(void);
};
