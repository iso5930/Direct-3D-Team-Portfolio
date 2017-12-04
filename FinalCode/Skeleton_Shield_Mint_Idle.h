#pragma once
#include "monsterstate.h"

class CSkeleton_Shield_Mint_Idle :
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
	CSkeleton_Shield_Mint_Idle(void);
	~CSkeleton_Shield_Mint_Idle(void);
};
