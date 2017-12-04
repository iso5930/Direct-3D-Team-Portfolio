#pragma once
#include "monsterstate.h"

class CGhoul_Idle :
	public CMonsterState
{
private:
	// πË»∏
	float	m_fHoverTime;
	int		m_iHover;

public:
	virtual void Initialize();
	virtual CMonsterState* Action();

public:
	explicit CGhoul_Idle(void);
	virtual ~CGhoul_Idle(void);
};
