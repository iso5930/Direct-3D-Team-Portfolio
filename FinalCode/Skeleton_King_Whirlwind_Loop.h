#pragma once
#include "monsterstate.h"

class CSkeleton_King_Whirlwind_Loop :
	public CMonsterState
{
private:
	int m_iMode;
	float m_fTime;
	int m_iEffect;	// 0 : 1타,	1 : 2타	

public:
	virtual void Initialize();
	virtual CMonsterState* Action();

private:
	// 한 애니메이션에서 두 번 공격에 따른 모드 추가.
	CMonsterState* Mode0();
	CMonsterState* Mode1();
	CMonsterState* Mode2();
	CMonsterState* Mode3();

public:
	explicit CSkeleton_King_Whirlwind_Loop(void);
	virtual ~CSkeleton_King_Whirlwind_Loop(void);
};
