#pragma once
#include "monsterstate.h"

class CSkeleton_Axe_Blue_Idle :
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
	explicit CSkeleton_Axe_Blue_Idle(void);
	virtual ~CSkeleton_Axe_Blue_Idle(void);
};
