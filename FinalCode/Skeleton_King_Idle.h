#pragma once
#include "monsterstate.h"

class CSkeleton_King_Idle :
	public CMonsterState
{
private:
	float m_fActSelectTime;
	float m_fWaitTime;
	int m_iMode;

public:
	virtual void Initialize();
	virtual CMonsterState* Action();

private:
	// 기본 대기
	CMonsterState* Mode0();
	
	// 공격전 대기
	CMonsterState* Mode1();

public:
	explicit CSkeleton_King_Idle(int _iMode);
	virtual ~CSkeleton_King_Idle(void);
};
