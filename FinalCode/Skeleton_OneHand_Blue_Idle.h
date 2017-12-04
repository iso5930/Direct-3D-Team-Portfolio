#pragma once
#include "monsterstate.h"

class CSkeleton_OneHand_Blue_Idle :
	public CMonsterState
{
private:
	// ��ȸ
	float	m_fHoverTime;
	int		m_iHover;

public:
	virtual void Initialize();
	virtual CMonsterState* Action();

public:
	explicit CSkeleton_OneHand_Blue_Idle(void);
	virtual ~CSkeleton_OneHand_Blue_Idle(void);
};
