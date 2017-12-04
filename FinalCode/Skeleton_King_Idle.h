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
	// �⺻ ���
	CMonsterState* Mode0();
	
	// ������ ���
	CMonsterState* Mode1();

public:
	explicit CSkeleton_King_Idle(int _iMode);
	virtual ~CSkeleton_King_Idle(void);
};
