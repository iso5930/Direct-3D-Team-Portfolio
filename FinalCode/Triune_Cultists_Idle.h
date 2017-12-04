#pragma once
#include "monsterstate.h"

class CTriune_Cultists_Idle :
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
	explicit CTriune_Cultists_Idle(void);
	virtual ~CTriune_Cultists_Idle(void);
};
