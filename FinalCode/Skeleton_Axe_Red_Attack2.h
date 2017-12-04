#pragma once
#include "monsterstate.h"

class CSkeleton_Axe_Red_Attack2 :
	public CMonsterState
{
private:
	// Mode
	int m_iMode;

	// Time
	float m_fTime;

public:
	virtual void Initialize();
	virtual CMonsterState* Action();

private:
	// Mode0
	CMonsterState* Mode0();

	// Mode1
	CMonsterState* Mode1();

public:
	explicit CSkeleton_Axe_Red_Attack2(void);
	virtual ~CSkeleton_Axe_Red_Attack2(void);
};
