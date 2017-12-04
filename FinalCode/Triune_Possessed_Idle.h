#pragma once
#include "monsterstate.h"

class CTriune_Possessed_Idle :
	public CMonsterState
{
private:
	// Mode
	int		m_iMode;

	// Worry
	float	m_fWorryTime;

	// πË»∏
	float	m_fHoverTime;
	int		m_iHover;

public:
	virtual void Initialize();
	virtual CMonsterState* Action();

private:
	CMonsterState* Mode0();
	CMonsterState* Mode1();

public:
	explicit CTriune_Possessed_Idle(int _iMode);
	virtual ~CTriune_Possessed_Idle(void);
};
