#pragma once
#include "monsterstate.h"

class CSkeleton_Axe_Red_Run :
	public CMonsterState
{
private:
	int m_iMode;
	float m_fTime;
	float m_fChaseTime;

public:
	virtual void Initialize();
	virtual CMonsterState* Action();

private:
	CMonsterState* Mode0();
	CMonsterState* Mode1();
	CMonsterState* Mode2();

public:
	explicit CSkeleton_Axe_Red_Run(int _iMode);
	virtual ~CSkeleton_Axe_Red_Run(void);
};
