#pragma once
#include "monsterstate.h"

class CSkeleton_King_Whirlwind_Loop :
	public CMonsterState
{
private:
	int m_iMode;
	float m_fTime;
	int m_iEffect;	// 0 : 1Ÿ,	1 : 2Ÿ	

public:
	virtual void Initialize();
	virtual CMonsterState* Action();

private:
	// �� �ִϸ��̼ǿ��� �� �� ���ݿ� ���� ��� �߰�.
	CMonsterState* Mode0();
	CMonsterState* Mode1();
	CMonsterState* Mode2();
	CMonsterState* Mode3();

public:
	explicit CSkeleton_King_Whirlwind_Loop(void);
	virtual ~CSkeleton_King_Whirlwind_Loop(void);
};
