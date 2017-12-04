#pragma once
#include "monsterstate.h"

class CSkeleton_King_Attack1 :
	public CMonsterState
{
private:
	// Mode
	int m_iMode;

	// Time
	float m_fTime;

	// Effect
	bool m_bEffect;

public:
	virtual void Initialize();
	virtual CMonsterState* Action();

private:
	// Mode0
	CMonsterState* Mode0();

	// Mode1
	CMonsterState* Mode1();

public:
	explicit CSkeleton_King_Attack1(void);
	virtual ~CSkeleton_King_Attack1(void);
};
