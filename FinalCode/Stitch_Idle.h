#pragma once
#include "monsterstate.h"

class CStitch_Idle :
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
	explicit CStitch_Idle(void);
	virtual ~CStitch_Idle(void);
};
